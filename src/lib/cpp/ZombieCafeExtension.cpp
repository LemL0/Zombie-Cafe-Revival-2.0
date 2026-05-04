#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/mman.h>
#include "Memory.h"

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "zombieCafeExtension::", __VA_ARGS__))


typedef jint (*jni_OnLoad)(JavaVM* vm, void* reserved);

static constexpr uintptr_t APP_HOLDER_OFFSET = 0x001daf80;
static constexpr uintptr_t ZOMBIE_CAFE_TOXIN_OFFSET = 0x000000b8;
static constexpr uintptr_t ZOMBIE_CAFE_MONEY_OFFSET = 0x000001ac;
static constexpr uintptr_t ZOMBIE_CAFE_LEVEL_XP_OFFSET = 0x000001b4;
static constexpr uintptr_t ZOMBIE_CAFE_TOTAL_XP_OFFSET = 0x000001b8;
static constexpr int32_t DEBUG_MAX_TOXIN = 999;
static constexpr int32_t DEBUG_MAX_MONEY = 999999;
static constexpr int32_t DEBUG_MAX_XP = 999999;

static void* getZombieCafeInstance() {
  uintptr_t base = reinterpret_cast<uintptr_t>(Memory::getBaseAddress());
  auto app = *reinterpret_cast<uintptr_t*>(base + APP_HOLDER_OFFSET);
  if (app == 0) {
    return nullptr;
  }

  auto game = *reinterpret_cast<uintptr_t*>(app + 0x4);
  if (game == 0) {
    return nullptr;
  }

  return reinterpret_cast<void*>(game);
}

extern "C" JNIEXPORT void JNICALL
Java_com_capcom_zombiecafeandroid_ZombieCafeAndroid_DebugAddMoney(JNIEnv*, jclass, jint amount) {
  auto cafe = reinterpret_cast<uint8_t*>(getZombieCafeInstance());
  if (cafe == nullptr) {
    LOGI("DebugAddMoney skipped because ZombieCafe instance is not ready");
    return;
  }

  auto money = reinterpret_cast<int32_t*>(cafe + ZOMBIE_CAFE_MONEY_OFFSET);
  int64_t next = static_cast<int64_t>(*money) + static_cast<int64_t>(amount);

  if (amount >= DEBUG_MAX_MONEY || next > DEBUG_MAX_MONEY) {
    next = DEBUG_MAX_MONEY;
  } else if (next < 0) {
    next = 0;
  }

  *money = static_cast<int32_t>(next);
  LOGI("DebugAddMoney set money to %d", *money);
}

extern "C" JNIEXPORT void JNICALL
Java_com_capcom_zombiecafeandroid_ZombieCafeAndroid_DebugSetToxin(JNIEnv*, jclass, jint amount) {
  auto cafe = reinterpret_cast<uint8_t*>(getZombieCafeInstance());
  if (cafe == nullptr) {
    LOGI("DebugSetToxin skipped because ZombieCafe instance is not ready");
    return;
  }

  int32_t next = amount;
  if (next > DEBUG_MAX_TOXIN) {
    next = DEBUG_MAX_TOXIN;
  } else if (next < 0) {
    next = 0;
  }

  *reinterpret_cast<int32_t*>(cafe + ZOMBIE_CAFE_TOXIN_OFFSET) = next;
  LOGI("DebugSetToxin set toxin to %d", next);
}

extern "C" JNIEXPORT void JNICALL
Java_com_capcom_zombiecafeandroid_ZombieCafeAndroid_DebugAddXp(JNIEnv*, jclass, jint amount) {
  auto cafe = reinterpret_cast<uint8_t*>(getZombieCafeInstance());
  if (cafe == nullptr) {
    LOGI("DebugAddXp skipped because ZombieCafe instance is not ready");
    return;
  }

  auto levelXp = reinterpret_cast<int32_t*>(cafe + ZOMBIE_CAFE_LEVEL_XP_OFFSET);
  auto totalXp = reinterpret_cast<float*>(cafe + ZOMBIE_CAFE_TOTAL_XP_OFFSET);
  int64_t next = static_cast<int64_t>(*levelXp) + static_cast<int64_t>(amount);

  if (amount >= DEBUG_MAX_XP || next > DEBUG_MAX_XP) {
    next = DEBUG_MAX_XP;
  } else if (next < 0) {
    next = 0;
  }

  *levelXp = static_cast<int32_t>(next);
  *totalXp += static_cast<float>(amount);
  if (*totalXp > static_cast<float>(DEBUG_MAX_XP)) {
    *totalXp = static_cast<float>(DEBUG_MAX_XP);
  } else if (*totalXp < 0.0f) {
    *totalXp = 0.0f;
  }

  LOGI("DebugAddXp set level XP to %d and total XP to %.0f", *levelXp, static_cast<double>(*totalXp));
}

extern "C" JNIEXPORT void JNICALL
Java_com_capcom_zombiecafeandroid_ZombieCafeAndroid_DebugSetXp(JNIEnv*, jclass, jint amount) {
  auto cafe = reinterpret_cast<uint8_t*>(getZombieCafeInstance());
  if (cafe == nullptr) {
    LOGI("DebugSetXp skipped because ZombieCafe instance is not ready");
    return;
  }

  int32_t next = amount;
  if (next > DEBUG_MAX_XP) {
    next = DEBUG_MAX_XP;
  } else if (next < 0) {
    next = 0;
  }

  *reinterpret_cast<int32_t*>(cafe + ZOMBIE_CAFE_LEVEL_XP_OFFSET) = next;
  *reinterpret_cast<float*>(cafe + ZOMBIE_CAFE_TOTAL_XP_OFFSET) = static_cast<float>(next);
  LOGI("DebugSetXp set level XP and total XP to %d", next);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
  LOGI("Zombie Cafe Extension Loaded!");
  int base = (int)Memory::getBaseAddress(); 
  
  const char* infoStr = "ZCR - %s\0";
  Memory::memcpyProtected((void*)(base + 0x1a14dc), infoStr, strlen(infoStr) + 1);

                          //http://zombiecafe.capcomcanada.com/updater/%s
  const char* updaterUrl = "https://zc.airyz.xyz/v1/updater/%s\0";
  Memory::memcpyProtected((void*)(base + 0x1a6610), updaterUrl, strlen(updaterUrl) + 1);

                    //http://zombiecafe.capcomcanada.com/x
  const char* xUrl = "https://zc.airyz.xyz/v1/x\0";
  Memory::memcpyProtected((void*)(base + 0x1a839c), xUrl, strlen(xUrl) + 1);

                      //http://zombiecafe.capcomcanada.com/zca
  const char* zcaUrl = "https://zc.airyz.xyz/v1/zca\0";
  Memory::memcpyProtected((void*)(base + 0x1a842c), zcaUrl, strlen(zcaUrl) + 1);


  Memory::setNop((void*)(base + 0x9dee8), 4);
  
  //Nop delete texture (this will cause memory leak, fix this!!!)
  Memory::setNop((void*)(base + 0x13d530), 4);
  Memory::setNop((void*)(base + 0x13d550), 4);
  Memory::setNop((void*)(base + 0x13d9e8), 4);
  Memory::setNop((void*)(base + 0x13d9ee), 4);


  /*  Fix crash when releasing texture reference also causes memory leak :( 
    #05 pc 0002eca7  /apex/com.android.runtime/lib/bionic/libc.so (scudo_free+18) (BuildId: 9e5101d790f828ae8b754029c778f7e2)
    #06 lib/arm/libZombieCafeAndroid.so (CFTextureRef::~CFTextureRef()+12)
    #07 lib/arm/libZombieCafeAndroid.so (CFTexture::releaseRef()+34)
    #08 lib/arm/libZombieCafeAndroid.so (CFTexture::~CFTexture()+4)
  */
  Memory::setNop((void*)(base + 0x0013d3ae), 4);
  Memory::setNop((void*)(base + 0x0013d3b4), 4);


  /* Patch to change Money Buy to Toxin Buy
    000ab018  d623       movs    r3, #0xd6    <-- change this offset to 0xb8
    000ab01a  5b00       lsls    r3, r3, #1   <-- prevent this leftshift
  */
  Memory::setProtection((void*)(base + 0xab018), 50, PROT_READ | PROT_WRITE | PROT_EXEC);
  *(char*)(base + 0x000ab018) = 0xb8;
  Memory::setNop((char*)(base + 0x000ab01a), 2);

  /*
    Stability patches from edbuildingstuff/zombie-cafe-revival.

    These avoid known Scudo heap-corruption crashes seen on newer Android
    builds during cafe transitions, path/move cleanup, and save hashing.
    They intentionally trade a small leak at those destruction sites for
    keeping the old native game running.
  */
  Memory::setNop((void*)(base + 0x679e4), 4);   // Cafe::~Cafe()
  Memory::setNop((void*)(base + 0x149c56), 4);  // PathTween::~PathTween()
  Memory::setNop((void*)(base + 0xe0a02), 2);   // MoveTask::~MoveTask()

  /*
    javaMD5String/javaMD5Data allocate 32 bytes and wrote the null
    terminator at byte 32. Move that terminator to byte 31 to avoid
    clobbering the next heap chunk header.
  */
  static const unsigned char movsR3_1F[] = {0x1F, 0x23};
  Memory::memcpyProtected((void*)(base + 0x17f318), movsR3_1F, sizeof(movsR3_1F));
  Memory::memcpyProtected((void*)(base + 0x17f7de), movsR3_1F, sizeof(movsR3_1F));

  return JNI_VERSION_1_4;
}
