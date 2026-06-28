#ifndef _LIBS_
#define _LIBS_

#include <string>
#include <format>
#include <sstream>
#include <iomanip>

#include "raylib.h"
#include "raymath.h"

#include "core/managers/assetmanager.h"
#include "core/managers/gamemanager.h"
#include "core/managers/scenemanager.h"
#include "core/managers/gfxmanager.h"
#include "core/managers/inputmanager.h"
#include "core/managers/serializationmanager.h"

#include "core/audioloader.h"
#include "core/spriteloader.h"

//nabutai vs entities v edin include file
#include "entities/player.h"
#include "entities/character.h"
#include "entities/coin.h"

#include "entities/factories/collectablefactory.h"
#include "entities/factories/enemyfactory.h"

#include "entities/characters/enemy.h"

#include "entities/factories/bulletfactory.h"

#include "entities/weapons/weapon.h"

#include "entities/bullets/bullet.h"

#endif