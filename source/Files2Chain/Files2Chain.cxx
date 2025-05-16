#include "Files2Chain.h"

int addFilesToChain(clas12root::HipoChain& chain, const std::string& directory) {
    int num_file = 0;
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.path().extension() == ".hipo") {
            chain.Add(entry.path().c_str());
            std::cout << "Added file: " << entry.path() << std::endl;
            num_file++;
        }
    }
    std::cout << "**************** " << num_file << " Files Loaded ****************" << std::endl;
    return num_file;
}