#include "blobstore.hpp"
#include "rust_cxx_probe/src/main.rs.h"

#include <string>
#include <iostream>
#include <format>

std::unique_ptr<BlobstoreClient> new_blobstore_client()
{
  return std::unique_ptr<BlobstoreClient>(new BlobstoreClient());
}

uint64_t BlobstoreClient::put(MultiBuf &buf) const
{
  // Traverse the caller's chunk iterator.
  std::string contents;
  while (true)
  {
    auto chunk = next_chunk(buf);
    if (chunk.size() == 0)
      break;

    contents.append(reinterpret_cast<const char *>(chunk.data()), chunk.size());
  }

  // Pretend we did something useful to persist the data.
  auto blobid = std::hash<std::string>{}(contents);

  std::cout << std::format("[C++]  blobid = {}\n", blobid);
  return blobid;
}
