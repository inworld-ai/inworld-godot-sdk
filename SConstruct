#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

env.Append(CPPDEFINES=["INWORLD_LOG=1"])
env.Append(CPPDEFINES=["INWORLD_LOG_CALLBACK=1"])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["Inworld/src/"])
sources = [
    Glob("Inworld/src/*.cpp")
]

if env["platform"] == "windows":

    Default(env.Install('Project/bin', 'Inworld/inworld-ndk/lib/Win64/webrtc_aec_plugin.dll'))

    env.Append(LIBPATH=['Inworld/curl-7.55.1/lib/Win64/VS2015'])
    env.Append(LIBS=['libcurl_a.lib'])

    env.Append(CPPPATH=['Inworld/inworld-ndk/src'])
    env.Append(CPPPATH=['Inworld/inworld-ndk/src/proto'])
    
    env.Append(CPPPATH=['Inworld/inworld-ndk/include'])

    env.Append(LIBPATH=['Inworld/inworld-ndk/lib/Win64'])
    env.Append(LIBS=['absl_bad_optional_access.lib','absl_status.lib','absl_time_zone.lib',
    'libssl.lib','absl_base.lib','absl_statusor.lib','address_sorting.lib','re2.lib','absl_cord.lib',
    'absl_str_format_internal.lib','cares.lib','upb.lib','absl_graphcycles_internal.lib',
    'absl_strings.lib','gpr.lib','webrtc_aec_plugin.dll','absl_int128.lib','absl_strings_internal.lib',
    'grpc.lib','webrtc_aec_plugin.dll.lib','absl_malloc_internal.lib','absl_symbolize.lib',
    'grpc++.lib','zlibstatic.lib','absl_raw_logging_internal.lib','absl_synchronization.lib','InworldNDK.lib',
    'absl_spinlock_wait.lib','absl_throw_delegate.lib','libcrypto.lib','absl_stacktrace.lib','absl_time.lib','libprotobuf.lib'])
    library = env.SharedLibrary(
        "Project/bin/libinworld{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
