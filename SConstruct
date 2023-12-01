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

    env.Append(LIBPATH=['Inworld/curl-7.55.1/lib/Win64/VS2015'])
    env.Append(LIBS=['libcurl_a.lib'])

    env.Append(CPPPATH=['Inworld/inworld-ndk/src'])
    env.Append(CPPPATH=['Inworld/inworld-ndk/src/proto'])
    
    env.Append(CPPPATH=['Inworld/inworld-ndk/include'])

    env.Append(LIBPATH=['Inworld/inworld-ndk/lib/Win64'])
    env.Append(LIBS=[
	'InworldNDK.lib',
    'absl_bad_optional_access.lib',
    'absl_base.lib',
    'absl_cord.lib',
    'absl_graphcycles_internal.lib',
    'absl_int128.lib',
    'absl_malloc_internal.lib',
    'absl_raw_logging_internal.lib',
    'absl_spinlock_wait.lib',
    'absl_stacktrace.lib',
    'absl_status.lib',
    'absl_statusor.lib',
    'absl_str_format_internal.lib',
    'absl_strings.lib',
    'absl_strings_internal.lib',
    'absl_symbolize.lib',
    'absl_synchronization.lib',
    'absl_throw_delegate.lib',
    'absl_time.lib',
    'absl_time_zone.lib',
    'address_sorting.lib',
    'cares.lib',
    'gpr.lib',
    'grpc++.lib',
    'grpc.lib',
    'libcrypto.lib',
    'libprotobuf.lib',
    'libssl.lib',
    're2.lib',
    'upb.lib',
    'zlibstatic.lib',
	])
    library = env.SharedLibrary(
        "Project/bin/libinworld{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
