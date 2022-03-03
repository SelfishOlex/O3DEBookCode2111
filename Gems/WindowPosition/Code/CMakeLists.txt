
# Currently we are in the Code folder: ${CMAKE_CURRENT_LIST_DIR}
# Get the platform specific folder ${pal_dir} for the current folder: ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME}
# Note: ly_get_list_relative_pal_filename will take care of the details for us, as this may be a restricted platform
#       in which case it will see if that platform is present here or in the restricted folder.
#       i.e. It could here in our gem : Gems/WindowPosition/Code/Platform/<platorm_name>  or
#            <restricted_folder>/<platform_name>/Gems/WindowPosition/Code
ly_get_list_relative_pal_filename(pal_dir ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME} ${o3de_gem_restricted_path} ${o3de_gem_path} ${o3de_gem_name})

# Now that we have the platform abstraction layer (PAL) folder for this folder, thats where we will find the
# traits for this platform. Traits for a platform are defines for things like whether or not something in this gem
# is supported by this platform.
include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake)

# Add the WindowPosition.Static target
# Note: We include the common files and the platform specific files which are set in windowposition_common_files.cmake
# and in ${pal_dir}/windowposition_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
ly_add_target(
    NAME WindowPosition.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        windowposition_files.cmake
        ${pal_dir}/windowposition_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
        PRIVATE
            Source
    BUILD_DEPENDENCIES
        PUBLIC
            AZ::AzCore
            AZ::AzFramework
)

# Here add WindowPosition target, it depends on the WindowPosition.Static
ly_add_target(
    NAME WindowPosition ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        windowposition_shared_files.cmake
        ${pal_dir}/windowposition_shared_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
        PRIVATE
            Source
    BUILD_DEPENDENCIES
        PRIVATE
            Gem::WindowPosition.Static
)

# By default, we will specify that the above target WindowPosition would be used by
# Client and Server type targets when this gem is enabled.  If you don't want it
# active in Clients or Servers by default, delete one of both of the following lines:
ly_create_alias(NAME WindowPosition.Clients NAMESPACE Gem TARGETS Gem::WindowPosition)
ly_create_alias(NAME WindowPosition.Servers NAMESPACE Gem TARGETS Gem::WindowPosition)

# If we are on a host platform, we want to add the host tools targets like the WindowPosition.Editor target which
# will also depend on WindowPosition.Static
if(PAL_TRAIT_BUILD_HOST_TOOLS)
    ly_add_target(
        NAME WindowPosition.Editor.Static STATIC
        NAMESPACE Gem
        FILES_CMAKE
            windowposition_editor_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                Source
            PUBLIC
                Include
        BUILD_DEPENDENCIES
            PUBLIC
                AZ::AzToolsFramework
                Gem::WindowPosition.Static
    )

    ly_add_target(
        NAME WindowPosition.Editor GEM_MODULE
        NAMESPACE Gem
        AUTOMOC
        FILES_CMAKE
            windowposition_editor_shared_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                Source
            PUBLIC
                Include
        BUILD_DEPENDENCIES
            PUBLIC
                Gem::WindowPosition.Editor.Static
    )

    # By default, we will specify that the above target WindowPosition would be used by
    # Tool and Builder type targets when this gem is enabled.  If you don't want it
    # active in Tools or Builders by default, delete one of both of the following lines:
    ly_create_alias(NAME WindowPosition.Tools    NAMESPACE Gem TARGETS Gem::WindowPosition.Editor)
    ly_create_alias(NAME WindowPosition.Builders NAMESPACE Gem TARGETS Gem::WindowPosition.Editor)


endif()

################################################################################
# Tests
################################################################################
# See if globally, tests are supported
if(PAL_TRAIT_BUILD_TESTS_SUPPORTED)
    # We globally support tests, see if we support tests on this platform for WindowPosition.Static
    if(PAL_TRAIT_WINDOWPOSITION_TEST_SUPPORTED)
        # We support WindowPosition.Tests on this platform, add WindowPosition.Tests target which depends on WindowPosition.Static
        ly_add_target(
            NAME WindowPosition.Tests ${PAL_TRAIT_TEST_TARGET_TYPE}
            NAMESPACE Gem
            FILES_CMAKE
                windowposition_files.cmake
                windowposition_tests_files.cmake
            INCLUDE_DIRECTORIES
                PRIVATE
                    Tests
                    Source
            BUILD_DEPENDENCIES
                PRIVATE
                    AZ::AzTest
                    AZ::AzFramework
                    Gem::WindowPosition.Static
        )

        # Add WindowPosition.Tests to googletest
        ly_add_googletest(
            NAME Gem::WindowPosition.Tests
        )
    endif()

    # If we are a host platform we want to add tools test like editor tests here
    if(PAL_TRAIT_BUILD_HOST_TOOLS)
        # We are a host platform, see if Editor tests are supported on this platform
        if(PAL_TRAIT_WINDOWPOSITION_EDITOR_TEST_SUPPORTED)
            # We support WindowPosition.Editor.Tests on this platform, add WindowPosition.Editor.Tests target which depends on WindowPosition.Editor
            ly_add_target(
                NAME WindowPosition.Editor.Tests ${PAL_TRAIT_TEST_TARGET_TYPE}
                NAMESPACE Gem
                FILES_CMAKE
                    windowposition_editor_tests_files.cmake
                INCLUDE_DIRECTORIES
                    PRIVATE
                        Tests
                        Source
                BUILD_DEPENDENCIES
                    PRIVATE
                        AZ::AzTest
                        Gem::WindowPosition.Editor
            )

            # Add WindowPosition.Editor.Tests to googletest
            ly_add_googletest(
                NAME Gem::WindowPosition.Editor.Tests
            )
        endif()
    endif()
endif()
