#include <std_include.hpp>
#include "io.hpp"

namespace iw4of::utils::io
{
  bool file_exists(const std::string& file)
  {
    return std::ifstream(file).good();
  }

  bool write_file(const std::string& file, const std::string& data,
                  const bool append)
  {
    const auto pos = file.find_last_of("/\\");
    if (pos != std::string::npos)
    {
      create_directory(file.substr(0, pos));
    }

    std::ofstream stream(
        file,
        std::ios::binary | std::ofstream::out |
            (append ? std::ofstream::app : std::ofstream::out));

    if (stream.is_open())
    {
      stream.write(data.data(), data.size());
      stream.close();
      return true;
    }

    return false;
  }

  std::string read_file(const std::string& file)
  {
    std::string data;
    read_file(file, &data);
    return data;
  }

  bool read_file(const std::string& file, std::string* data)
  {
    if (!data) return false;
    data->clear();

    if (file_exists(file))
    {
      std::ifstream stream(file, std::ios::binary);
      if (!stream.is_open()) return false;

      stream.seekg(0, std::ios::end);
      const std::streamsize size = stream.tellg();
      stream.seekg(0, std::ios::beg);

      if (size > -1)
      {
        data->resize(static_cast<uint32_t>(size));
        stream.read(data->data(), size);
        stream.close();
        return true;
      }
    }

    return false;
  }

  size_t file_size(const std::string& file)
  {
    if (file_exists(file))
    {
      std::ifstream stream(file, std::ios::binary);

      if (stream.good())
      {
        stream.seekg(0, std::ios::end);
        return static_cast<size_t>(stream.tellg());
      }
    }

    return 0;
  }

  bool create_directory(const std::string& directory)
  {
    return std::filesystem::create_directories(directory);
  }

  bool directory_exists(const std::string& directory)
  {
    return std::filesystem::is_directory(directory);
  }

  bool directory_is_empty(const std::string& directory)
  {
    return std::filesystem::is_empty(directory);
  }

  std::vector<std::string> list_files(const std::string& directory)
  {
    std::vector<std::string> files;

    for (auto& file : std::filesystem::directory_iterator(directory))
    {
      files.push_back(file.path().generic_string());
    }

    return files;
  }
} // namespace iw4of::utils::io
