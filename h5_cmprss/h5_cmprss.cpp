#include "h5_cmprss.h"

const int	DIM0 = 9600;
const int	DIM1 = 240;

int
main(int argc, char **argv) {
  // Try block to detect exceptions raised by any of the calls inside it
  try {
    // Turn off the auto-printing when failure occurs so that we can
    // handle the errors appropriately
    H5std_string FILE_NAME(argv[1]);
    Exception::dontPrint();

    // Open the file and the dataset in the file.
    H5File file(FILE_NAME, H5F_ACC_RDONLY);

    DataSet dataset;
    H5std_string dataset_name;
    auto objCount(H5Fget_obj_count(file.getId(), H5F_OBJ_ALL));
    for (size_t i = 0; i != objCount; ++i)
      if (H5G_DATASET == file.getObjTypeByIdx(i)) {
	dataset_name = file.getObjnameByIdx(i);
	dataset = file.openDataSet(dataset_name);
      }

    auto datatype(dataset.getDataType());
    auto dataspace(dataset.getSpace());

    hsize_t dims_in[2];
    auto ndims(dataspace.getSimpleExtentDims(dims_in, NULL));

    hsize_t dims_out[2] = { DIM0, DIM1 };	// dataset dimensions

    double *buf = new double[dims_in[0] * dims_in[1]];

    // Read data.
    dataset.read(buf, PredType::NATIVE_DOUBLE);//, memspace, dataspace);

    H5std_string outFileName("out.h5");

    // Create a new file using the default property lists. 
    H5File outfile(outFileName, H5F_ACC_TRUNC);

    // Create the data space for the dataset.
    DataSpace *output_dataspace = new DataSpace(ndims, dims_out);

    hsize_t chunk_dims[2] = { 20, 20 };	// chunk dimensions
    // Modify dataset creation property to enable chunking
    DSetCreatPropList *plist = new DSetCreatPropList;
    plist->setChunk(2, chunk_dims);

    // Set ZLIB (DEFLATE) Compression using level 9.
    plist->setDeflate(9);

    // Create the attributes.
    const size_t numAttrs = file.getNumAttrs();
    for (size_t i = 0; i != numAttrs; ++i) {
      auto attr(file.openAttribute(i));
      auto output_attr(outfile.createAttribute(attr.getName(), 
					       attr.getDataType(), 
					       attr.getSpace()));

      switch (attr.getTypeClass()) {
      case H5T_FLOAT: {
	double buf;
    	attr.read(attr.getDataType(), &buf);
    	output_attr.write(attr.getDataType(), &buf);
      }
	break;
      case H5T_STRING: {
	char *buf = new char[(unsigned long)attr.getStorageSize()];
    	attr.read(attr.getDataType(), buf);
    	output_attr.write(attr.getDataType(), buf);
	delete buf;
      }
	break;
      default:
	break;
      }
    }

    // Create the dataset.      
    DataSet *output_dataset = new DataSet(outfile.createDataSet(dataset_name, datatype, *output_dataspace, *plist));

    // Write data to dataset.
    output_dataset->write(buf, datatype);

    // Close objects and file.  Either approach will close the HDF5 item.
    delete output_dataspace;
    delete output_dataset;
    delete plist;
    file.close();
  }  // end of try block

  // catch failure caused by the H5File operations
  catch(FileIException &error) {
    error.printError();
    return -1;
  }

  // catch failure caused by the DataSet operations
  catch(DataSetIException &error) {
    error.printError();
    return -1;
  }

  // catch failure caused by the DataSpace operations
  catch(DataSpaceIException &error) {
    error.printError();
    return -1;
  }

  // catch failure caused by the Attribute operations
  catch (AttributeIException &error) {
    error.printError();
    return -1;
  }

  catch (std::exception &error) {
    std::cerr << error.what() << std::endl;
    return -1;
  }

  return 0;  // successfully terminated
}
