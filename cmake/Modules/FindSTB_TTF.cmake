IF(STB_TTF_INCLUDE_DIR)
  # in cache already
  SET(STB_TTF_FIND_QUIETLY TRUE)
ENDIF(STB_TTF_INCLUDE_DIR)

FIND_PATH(STB_TTF_INCLUDE_DIR
	stb_truetype.h
	PATHS
	$ENV{STB_TTF_DIR}/
	/usr/local/include/
	/usr/include/
	/opt/local/include/
	/opt/include/
)

if (STB_TTF_INCLUDE_DIR)
	MESSAGE(STATUS "Found STB_TTF_INCLUDE_DIR: ${STB_TTF_INCLUDE_DIR}")
	SET(STB_TTF_FOUND "YES")
ELSE(STB_TTF_INCLUDE_DIR)
	IF(NOT STB_TTF_FIND_QUIETLY)
		IF (STB_TTF_FIND_REQUIRED)
			MESSAGE(FATAL_ERROR "ERROR: Cannot find STB TTF!")
		ELSE (STB_TTF_FIND_REQUIRED)
			MESSAGE(STATUS "Warning: Unable to find STB TTF!")
		ENDIF (STB_TTF_FIND_REQUIRED)
	ENDIF(NOT STB_TTF_FIND_QUIETLY)
ENDIF(STB_TTF_INCLUDE_DIR)
