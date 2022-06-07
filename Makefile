TARGET = LauAnalysis
CC     = mpiicc
CFLAGS = -O3  -g -Wall -I${DIR_INC}

DIR_INC = include
DIR_SRC = src
DIR_OBJ = obj
DIR_BIN = bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC}))

BIN_TARGET = ${DIR_BIN}/${TARGET}

${BIN_TARGET}:${OBJ} ${DIR_BIN}
	$(CC) $(OBJ)  -o $@
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp ${DIR_OBJ}
	$(CC) $(CFLAGS) -c  $< -o $@

${DIR_BIN}:
	@-mkdir ${DIR_BIN}
${DIR_OBJ}:
	@-mkdir ${DIR_OBJ}

.PHONY:clean
clean:
	rm ${DIR_OBJ}/*.o  
	rm -rf $(BIN_TARGET)
