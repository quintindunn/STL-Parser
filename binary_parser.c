//
// Created by Quintin Dunn on 12/12/24.
//

#define HEADER_SIZE 80
#define HEADING_OFFSET 84
#define FACE_SIZE 50

#include "binary_parser.h"
#include <stdio.h>
#include <string.h>

void print_vector(const vector3 vec) {
	printf("vector3(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

void print_face(const face triangle) {
	printf("Normal: ");
	print_vector(triangle.normal_vector);
	printf("A: \t\t");
	print_vector(triangle.a);
	printf("B: \t\t");
	print_vector(triangle.b);
	printf("C: \t\t");
	print_vector(triangle.c);
	printf("Attributes: %hu", triangle.attributes);
}

void print_hex(const unsigned char *buffer, size_t length) {
	for (size_t i = 0; i < length; i++) {
		printf("%02X ", buffer[i]);
	}
	printf("\n");
}

face* binary_stl_parser(const char* content, size_t size) {
	// Header: first 80 bytes
	// Number of triangles: next 4 bytes
	// For each triangle:
	// Start idx = 84+i*50;
	// normal vector: next 12 bytes
	// vertex 1: next 12 bytes
	// vertex 2: next 12 bytes
	// vertex 3 : next 12 bytes
	// attributes: next 2 bytes
	if (size < 84) {
		perror("Invalid file!");
		return NULL;
	}

	char header[HEADER_SIZE];
	unsigned int triangle_count;
	memcpy(&header, content, HEADER_SIZE);
	memcpy(&triangle_count, &content[HEADER_SIZE], sizeof(unsigned int));

	face* faces = malloc(triangle_count*sizeof(face));

	for (int i = 0; i < triangle_count; i++) {
		face triangle;
		memcpy(&triangle, &content[HEADING_OFFSET+i*FACE_SIZE], sizeof(face));
		faces[i] = triangle;

	}

	return faces;
}
