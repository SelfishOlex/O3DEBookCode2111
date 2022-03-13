
set(FILES
    Source/MyGemModuleInterface.h
    Source/MyGemSystemComponent.cpp
    Source/MyGemSystemComponent.h
    Include/MyGem/UiScoreBus.h
    Source/UiScoreComponent.cpp
    Source/UiScoreComponent.h
    Source/KickingComponent.cpp
    Source/KickingComponent.h
    Source/ChickenAnimationComponent.cpp
    Source/ChickenAnimationComponent.h
    Include/MyGem/ChickenBus.h

    Source/AutoGen/MyFirstNetworkComponent.AutoComponent.xml
    Source/Multiplayer/MyFirstNetworkComponent.h
    Source/Multiplayer/MyFirstNetworkComponent.cpp

    Source/ChickenSpawnComponent.h
    Source/ChickenSpawnComponent.cpp
    Source/AutoGen/ChickenComponent.AutoComponent.xml
    Source/Multiplayer/ChickenComponent.h
    Source/Multiplayer/ChickenComponent.cpp

    Source/AutoGen/ChickenMovementComponent.AutoComponent.xml
    Source/Multiplayer/ChickenMovementComponent.h
    Source/Multiplayer/ChickenMovementComponent.cpp

    Source/AutoGen/GoalDetectorComponent.AutoComponent.xml
    Source/Multiplayer/GoalDetectorComponent.cpp
    Source/Multiplayer/GoalDetectorComponent.h

    # new
    Include/MyGem/BallBus.h
    Include/MyGem/BallSpawnerBus.h
    Source/AutoGen/BallSpawnerComponent.AutoComponent.xml
    Source/Multiplayer/BallSpawnerComponent.cpp
    Source/Multiplayer/BallSpawnerComponent.h
    Source/AutoGen/BallComponent.AutoComponent.xml
    Source/Multiplayer/BallComponent.cpp
    Source/Multiplayer/BallComponent.h
)
