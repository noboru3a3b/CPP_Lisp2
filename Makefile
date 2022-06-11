object_test:
	g++ object.cpp object_test.cpp

atom_test:
	g++ object.cpp atom.cpp string.cpp num_int.cpp atom_test.cpp

string_test:
	g++ object.cpp string.cpp string_test.cpp

num_int_test:
	g++ object.cpp num_int.cpp num_int_test.cpp

num_float_test:
	g++ object.cpp num_float.cpp num_float_test.cpp

cell_test:
	g++ object.cpp atom.cpp cell.cpp cell_test.cpp

full_member_test:
	g++ object.cpp atom.cpp string.cpp num_int.cpp num_float.cpp cell.cpp \
	full_member_test.cpp

vector_test:
	g++ object.cpp atom.cpp vector.cpp vector_test.cpp

atom_map_test:
	g++ object.cpp atom.cpp atom_map.cpp atom_map_test.cpp

read_test:
	g++ -std=c++1z -g object.cpp atom.cpp string.cpp num_int.cpp num_float.cpp \
	cell.cpp vector.cpp atom_map.cpp int_map.cpp float_map.cpp read_test.cpp

clean:
	rm a.out
