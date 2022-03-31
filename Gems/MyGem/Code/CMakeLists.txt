
# Currently we are in the Code folder: ${CMAKE_CURRENT_LIST_DIR}
# Get the platform specific folder ${pal_dir} for the current folder: ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME}
# Note: ly_get_list_relative_pal_filename will take care of the details for us, as this may be a restricted platform
#       in which case it will see if that platform is present here or in the restricted folder.
#       i.e. It could here in our gem : Gems/MyGem/Code/Platform/<platorm_name>  or
#            <restricted_folder>/<platform_name>/Gems/MyGem/Code
ly_get_list_relative_pal_filename(pal_dir ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME} ${o3de_gem_restricted_path} ${o3de_gem_path} ${o3de_gem_name})

# Now that we have the platform abstraction layer (PAL) folder for this folder, thats where we will find the
# traits for this platform. Traits for a platform are defines for things like whether or not something in this gem
# is supported by this platform.
include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake)

# Add the MyGem.Static target
# Note: We include the common files and the platform specific files which are set in mygem_common_files.cmake
# and in ${pal_dir}/mygem_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
ly_add_target(
    NAME MyGem.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        mygem_files.cmake
        mygem_autogen_files.cmake
        ${pal_dir}/mygem_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
        PRIVATE
            Source
    BUILD_DEPENDENCIES
        PUBLIC
            AZ::AzCore
            AZ::AzFramework
            Gem::StartingPointInput.Static
            Gem::LyShine.Static
            Gem::PhysX.Static
            Gem::EMotionFXStaticLib
            # For autogen components
            Gem::Multiplayer.Static
    AUTOGEN_RULES
        *.AutoComponent.xml,AutoComponent_Header.jinja,$path/$fileprefix.AutoComponent.h
        *.AutoComponent.xml,AutoComponent_Source.jinja,$path/$fileprefix.AutoComponent.cpp
        *.AutoComponent.xml,AutoComponentTypes_Header.jinja,$path/AutoComponentTypes.h
        *.AutoComponent.xml,AutoComponentTypes_Source.jinja,$path/AutoComponentTypes.cpp
)

# Here add MyGem target, it depends on the MyGem.Static
ly_add_target(
    NAME MyGem ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        mygem_shared_files.cmake
        ${pal_dir}/mygem_shared_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
        PRIVATE
            Source
    BUILD_DEPENDENCIES
        PRIVATE
            Gem::MyGem.Static
)

# By default, we will specify that the above target MyGem would be used by
# Client and Server type targets when this gem is enabled.  If you don't want it
# active in Clients or Servers by default, delete one of both of the following lines:
ly_create_alias(NAME MyGem.Clients NAMESPACE Gem TARGETS Gem::MyGem)
ly_create_alias(NAME MyGem.Servers NAMESPACE Gem TARGETS Gem::MyGem)

# If we are on a host platform, we want to add the host tools targets like the MyGem.Editor target which
# will also depend on MyGem.Static
if(PAL_TRAIT_BUILD_HOST_TOOLS)
    ly_add_target(
        NAME MyGem.Editor.Static STATIC
        NAMESPACE Gem
        FILES_CMAKE
            mygem_editor_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                Source
            PUBLIC
                Include
        BUILD_DEPENDENCIES
            PUBLIC
                AZ::AzToolsFramework
                Gem::MyGem.Static
    )

    ly_add_target(
        NAME MyGem.Editor GEM_MODULE
        NAMESPACE Gem
        AUTOMOC
        FILES_CMAKE
            mygem_editor_shared_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                Source
            PUBLIC
                Include
        BUILD_DEPENDENCIES
            PUBLIC
                Gem::MyGem.Editor.Static
    )

    # By default, we will specify that the above target MyGem would be used by
    # Tool and Builder type targets when this gem is enabled.  If you don't want it
    # active in Tools or Builders by default, delete one of both of the following lines:
    ly_create_alias(NAME MyGem.Tools    NAMESPACE Gem TARGETS Gem::MyGem.Editor)
    ly_create_alias(NAME MyGem.Builders NAMESPACE Gem TARGETS Gem::MyGem.Editor)


endif()

################################################################################
# Tests
################################################################################
# See if globally, tests are supported
if(PAL_TRAIT_BUILD_TESTS_SUPPORTED)
    # We globally support tests, see if we support tests on this platform for MyGem.Static
    if(PAL_TRAIT_MYGEM_TEST_SUPPORTED)
        # We support MyGem.Tests on this platform, add MyGem.Tests target which depends on MyGem.Static
        ly_add_target(
            NAME MyGem.Tests ${PAL_TRAIT_TEST_TARGET_TYPE}
            NAMESPACE Gem
            FILES_CMAKE
                mygem_tests_files.cmake
            INCLUDE_DIRECTORIES
                PRIVATE
                    Tests
                    Source
            BUILD_DEPENDENCIES
                PRIVATE
                    AZ::AzTest
                    AZ::AzFramework
                    Gem::MyGem.Static
        )

        # Add MyGem.Tests to googletest
        ly_add_googletest(
            NAME Gem::MyGem.Tests
        )
    endif()

    # If we are a host platform we want to add tools test like editor tests here
    if(PAL_TRAIT_BUILD_HOST_TOOLS)
        # We are a host platform, see if Editor tests are supported on this platform
        if(PAL_TRAIT_MYGEM_EDITOR_TEST_SUPPORTED)
            # We support MyGem.Editor.Tests on this platform, add MyGem.Editor.Tests target which depends on MyGem.Editor
            ly_add_target(
                NAME MyGem.Editor.Tests ${PAL_TRAIT_TEST_TARGET_TYPE}
                NAMESPACE Gem
                FILES_CMAKE
                    mygem_editor_tests_files.cmake
                INCLUDE_DIRECTORIES
                    PRIVATE
                        Tests
                        Source
                BUILD_DEPENDENCIES
                    PRIVATE
                        AZ::AzTest
                        Gem::MyGem.Editor
            )

            # Add MyGem.Editor.Tests to googletest
            ly_add_googletest(
                NAME Gem::MyGem.Editor.Tests
            )
        endif()
    endif()
endif()
