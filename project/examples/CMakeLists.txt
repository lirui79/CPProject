AUX_SOURCE_DIRECTORY(. DIR_TEST_SRCS)
add_executable( Test ${DIR_TEST_SRCS})


set(Use_MyMath 0)
# 是否加入 MathFuntion 库
if (USE_MYMATH)
  set(Use_MyMath 1)
endif (USE_MYMATH)

if (NOT HAVE_POW)
  set(Use_MyMath 1)
endif (NOT HAVE_POW)

if (Use_MyMath)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFuntion)
endif (Use_MyMath)

target_link_libraries(Test  pthread dl Log Common ModuleManager ${EXTRA_LIBS})
