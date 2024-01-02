cd App/Helpers
gcc -c UserHelper.c && ar crv UserHelper.a UserHelper.o && ranlib UserHelper.a
rm UserHelper.o
cd ../Controllers
gcc -c UserController.c && ar crv User.a UserController.o && ranlib User.a
gcc -c SocketController.c && ar crv Socket.a SocketController.o && ranlib Socket.a
gcc -c FileController.c && ar crv File.a FileController.o && ranlib File.a
rm UserController.o SocketController.o FileController.o
cd ../..
gcc -c main.c && gcc -o main main.o App/Controllers/User.a App/Controllers/Socket.a App/Helpers/UserHelper.a App/Controllers/File.a
rm main.o