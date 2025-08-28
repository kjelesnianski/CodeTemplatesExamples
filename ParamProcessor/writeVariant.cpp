#include <cstring>
#include <fstream>
#include <istream>
#include <iostream>
#include <memory>
#include <vector>

#define MAGIC_NUM_LEN 4
#define JSON_FILE_LEN 4

std::string getFilenameFromPath(const std::string& path) {
    size_t lastSlashPos = path.find_last_of("/\\");

    if (lastSlashPos != std::string::npos) {
        return path.substr(lastSlashPos + 1);
    } else {
        return path;
    }
}
/* ret: returns number of bytes written
 */
int writeToBinary(
    const std::string& binaryPath,
    const std::unique_ptr<const char[]>& magicNumber,
    const std::string jsonFile = "")
{
  std::string binaryFile = getFilenameFromPath(binaryPath);
  std::string outputFile = jsonFile.empty() ? (binaryFile + ".00") : (binaryFile + ".V");

  //Open file binary mode
  std::ifstream in(binaryPath, std::ios::binary);
  if(!in) {
    std::cout << "Could not open binary file: " << binaryPath << std::endl;
    return 1;
  }

  std::ofstream out(outputFile, std::ios::binary);
  if(!out) {
    std::cout << "Could not open new file to write to: " << outputFile << std::endl;
    return 1;
  }

  // First copy over base contents
  out << in.rdbuf();
  bool success_copy = in.good() && out.good();
  if(!success_copy) {
    std::cout << "Error copying file contents" << std::endl;
    return 1;
  }

  // Write magic number
  out.write(magicNumber.get(), MAGIC_NUM_LEN);

  if(!jsonFile.empty()){
    auto jsonFileLen = 0;
    //Open JSON file to determine length, open as binary and seek to end immediately after open
    std::ifstream json(jsonFile, std::ios::binary | std::ios::ate);
    if(!json) {
      std::cout << "Could not open JSON file: " << jsonFile << std::endl;
      return 1;
    }
    jsonFileLen = json.tellg();
    if(jsonFileLen < 0) {
      std::cout << "Could not determine JSON size" << std::endl;
      return 1;
    }

    auto buffer = std::make_unique<char[]>(static_cast<size_t>(jsonFileLen));
    // seek to the beginning of the file
    json.seekg(0, std::ios::beg); // Move to start of file
    // Populate buffer
    json.read(buffer.get(), jsonFileLen);
    
    //write json file
    out.write(buffer.get(),jsonFileLen);

    //write json file size
    out.write(reinterpret_cast<const char*>(&jsonFileLen), JSON_FILE_LEN);
  }

  return 0;
}

int main(int argc, char** argv) {
  std::cout << "ARGC: " << argc << std::endl;

  if (argc != 3 && argc != 4) {
      std::cout << "Usage: " << argv[0] << " <binaryFile> <hex_number> (<jsonFile>)" << std::endl;
      return 1;
  }

  // Get the hex number string
  const char* hex_input = argv[2];
  // Validate hex number
  if (strncmp(hex_input, "0x", 2) == 0 || strncmp(hex_input, "0X", 2) == 0) {
      hex_input += 2; // Skip '0x' prefix
  }
  // Check if the remaining string is a valid hex number
  for (size_t i = 0; hex_input[i] != '\0'; ++i) {
      if (!isxdigit(hex_input[i])) {
          std::cout << "Error: Invalid hex number" << std::endl;
          return 1;
      }
  }

  // Arg1 Binary File
  std::string binaryFile;
  // Arg2 magic number (4 byte)
  std::unique_ptr<const char[]> magicNumber = std::make_unique<const char[]>(MAGIC_NUM_LEN + 1);
  strcpy(const_cast<char*>(magicNumber.get()), hex_input);
  // Arg3 JSON file
  std::string jsonFile;
 
  //TODO check args
  binaryFile = argv[1];
  //char* magicNumber; = argv[2];

  if(argc == 3){
    // Write BASE
    std::cout << "Writing BASE [" << binaryFile << "] MAGIC: "  << magicNumber.get() << std::endl;
    if(writeToBinary(binaryFile, magicNumber) == 1) {
      std::cout << "Error writing BASE" << std::endl;
      return 1;
    }
  } else if(argc == 4) {
    // Fetch last arg for JSON
    jsonFile = argv[3];

    //Write Variant
    if(writeToBinary(binaryFile, magicNumber, jsonFile)) {
      std::cout << "Error writing variant" << std::endl;
      return 1;
    }
  }

  return 0;
}
