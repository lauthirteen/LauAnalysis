TARGET = LauAnalysis
CC     = mpiicc
CFLAGS = -O3  -g -Wall -I${DIR_INC}

#把所有的目录做成变量，方便修改和移植   
DIR_INC = include
DIR_SRC = src
DIR_OBJ = obj
DIR_BIN = bin
#提前所有源文件(即：*.c文件)和所有中间文件(即：*.o)  
SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC}))

#设置最后目标文件  
BIN_TARGET = ${DIR_BIN}/${TARGET}

#用所有中间文件生成目的文件，规则中可以用 $^替换掉 ${OBJECT}  
${BIN_TARGET}:${OBJ} ${DIR_BIN}
	$(CC) $(OBJ)  -o $@
#生成各个中间文件 
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
