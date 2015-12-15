ROOT=../..
SRC=${ROOT}/src
INC=${ROOT}/inc
RES=${ROOT}/res
PROJ_WIN32=${ROOT}/proj/win32

all: ready
	@g++ ./temp/*.cpp -o ./picker.a
	@rm -rf ./temp

ready: clean
	@mkdir -p temp
	@cp ${SRC}/* ./temp/
	@cp ${INC}/* ./temp/
	@cp ./main.cpp ./temp/

clean:
	@rm -rf ./temp
	@rm -rf *.a
