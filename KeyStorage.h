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

#ifndef ANDROID_VOLD_KEYSTORAGE_H
#define ANDROID_VOLD_KEYSTORAGE_H

#include "KeyBuffer.h"

#include <cstdint>
#include <string>
#include <vector>

namespace android {
namespace vold {

// Represents the information needed to decrypt a disk encryption key.
class KeyAuthentication {
  public:
    KeyAuthentication(const std::string& s) : secret{s} {};

    bool usesKeystore() const { return secret.empty(); };

    const std::string secret;
};

extern const KeyAuthentication kEmptyAuthentication;

bool createSecdiscardable(const std::string& path, std::string* hash);
bool readSecdiscardable(const std::string& path, std::string* hash);

void DeferredCommitKeystoreKeys();

// Renames a key directory while also managing deferred commits appropriately.
// This method should be used whenever a key directory needs to be moved/renamed.
bool RenameKeyDir(const std::string& old_name, const std::string& new_name);

// Create a directory at the named path, and store "key" in it as storeKey
// This version creates the key in "tmp_path" then atomically renames "tmp_path"
// to "key_path" thereby ensuring that the key is either stored entirely or
// not at all.  All the needed files and directories are also fsync'ed to ensure
// that the key is actually persisted to disk.
bool storeKeyAtomically(const std::string& key_path, const std::string& tmp_path,
                        const KeyAuthentication& auth, const KeyBuffer& key);

// Retrieve the key from the named directory.
//
// If the key is wrapped by a Keymaster key that requires an upgrade, then that
// Keymaster key is upgraded.  
bool retrieveKey(const std::string& dir, const KeyAuthentication& auth, KeyBuffer* key);

// Securely destroy the key stored in the named directory and delete the directory.
bool destroyKey(const std::string& dir);

bool runSecdiscardSingle(const std::string& file);

// Generate wrapped storage key using keystore. Uses STORAGE_KEY tag in keystore.
bool generateWrappedStorageKey(KeyBuffer* key);
// Export the per-boot boot wrapped storage key using keystore.
bool exportWrappedStorageKey(const KeyBuffer& ksKey, KeyBuffer* key);

// Set a seed to be mixed into all key storage encryption keys.
bool setKeyStorageBindingSeed(const std::vector<uint8_t>& seed);
}  // namespace vold
}  // namespace android

#endif
