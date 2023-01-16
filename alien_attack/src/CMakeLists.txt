file(GLOB AT_Source
    "*.cpp"
)
target_sources(AlienAttack
    PUBLIC
        ${AT_Source}
)
