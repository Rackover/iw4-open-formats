#pragma once

#include "assets/asset_interface.hpp"

namespace iw4of::interfaces
{
  struct iloadedsound : asset_interface
  {
   public:
    iloadedsound(const iw4of::assets* assets)
        : asset_interface(assets)
    {
    }

   protected:
    bool write_internal(const native::XAssetHeader& header) const override;
    void* read_internal(const std::string& name) const override;
    std::filesystem::path get_file_name(
        const std::string& basename) const override;
    std::filesystem::path get_folder_name() const override;
  };
} // namespace iw4of::interfaces