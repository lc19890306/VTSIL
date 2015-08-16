#include "h5fileanalyzer.h"

H5FileAnalyzer::H5FileAnalyzer(const int &argc, const QStringList &argv)
{
    clean_flag = false;
    try {
        H5std_string FILE_NAME = (1 == argc ? "out.h5" : argv[1].toUtf8().constData());
        H5::Exception::dontPrint();

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

        auto ndims(dataspace.getSimpleExtentNdims());
        hsize_t *dims = new hsize_t[ndims];
        dataspace.getSimpleExtentDims(dims, NULL);

        dim = 1;
        for (size_t i(0); i != ndims; ++i)
            dim *= dims[i];
        points = new double[dim];
        clean_flag = true;

        // Read data.
        dataset.read(points, PredType::NATIVE_DOUBLE);
        delete []dims;
    }

    // catch failure caused by the H5File operations
    catch(FileIException &error) {
        error.printError();
        if (clean_flag)
            clean();
        exit(-1);
    }

    // catch failure caused by the DataSet operations
    catch(DataSetIException &error) {
        error.printError();
        if (clean_flag)
            clean();
        exit(-1);
    }

    // catch failure caused by the DataSpace operations
    catch(DataSpaceIException &error) {
        error.printError();
        if (clean_flag)
            clean();
        exit(-1);
    }

    // catch failure caused by the Attribute operations
    catch (AttributeIException &error) {
        error.printError();
        if (clean_flag)
            clean();
        exit(-1);
    }

    catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
        if (clean_flag)
            clean();
        exit(-1);
    }

}

H5FileAnalyzer::~H5FileAnalyzer()
{
    if (clean_flag)
        clean();
}

void
H5FileAnalyzer::clean()
{
    delete [] points;
    clean_flag = false;
}
