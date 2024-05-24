#include <iostream>
#include <stdexcept>

class BinaryMap {
	private:
		void check_bounds(int column, int row) {
			if (column >= this->width) {
				throw std::invalid_argument("column is >= width");
			}

			if (row >= this->height) {
				throw std::invalid_argument("row is >= height");
			}
		}

		int index_from_column_and_row(int column, int row) {
			return column * this->width + row;
		}

		bool* start_of_binary_map;
		int map_size;
		int height;
		int width;

	public:
		BinaryMap(int height, int width) {

			this->height = height;
			this->width = width;
			this->map_size = height*width;
			this->start_of_binary_map = (bool*)malloc(this->map_size * sizeof(bool));
			
			for(int i = 0; i < map_size; i++) {
				this->start_of_binary_map[i] = false;
			}
		}

		~BinaryMap() {
			free(this->start_of_binary_map);
		}

		bool read(int column, int row) {
			this->check_bounds(column, row);
			int index = this->index_from_column_and_row(column,row);
			return this->start_of_binary_map[index];
		}

		void write(int column, int row, bool value) {
			this->check_bounds(column, row);
			int index = this->index_from_column_and_row(column,row);
			this->start_of_binary_map[index] = value;
		}
};

int main() {
	auto map = BinaryMap(5,4);
	map.write(1,3,1);
	std::cout << map.read(1,3) << '\n';

}
