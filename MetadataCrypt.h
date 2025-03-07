/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _METADATA_CRYPT_H
#define _METADATA_CRYPT_H

#include <fs_mgr.h>
#include <string>

#include "KeyBuffer.h"
#include "KeyUtil.h"

namespace android {
namespace vold {

void defaultkey_precreate_dm_device();
bool fscrypt_mount_metadata_encrypted(const std::string& block_device,
                                      const std::string& mount_point, bool needs_encrypt,
                                      bool should_format, const std::string& fs_type,
                                      const std::string& zoned_device, std::string fstab_path = "");

bool defaultkey_volume_keygen(KeyGeneration* gen);

bool defaultkey_setup_ext_volume(const std::string& label, const std::string& blk_device,
                                 const android::vold::KeyBuffer& key,
                                 std::string* out_crypto_blkdev);

bool destroy_dsu_metadata_key(const std::string& dsu_slot);

}  // namespace vold
}  // namespace android
#endif
