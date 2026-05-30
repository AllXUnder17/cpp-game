#ifndef _COLLECTABLE_FACTORY_
#define _COLLECTABLE_FACTORY_

#include "entities/coin.h"
class CollectableFactory {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    CollectableFactory() = delete;

    static void Init();
    
    //===DESTRUCTOR===
    static void Uninit();
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static Coin* SpawnCoin(const Vector2& pos);
private:
    static Coin* baseCoinPrefab;

    static void InitPrefabs();
};

#endif