#include <iostream>
#include <cmath>
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
			return column + row * this->width;
		}

		void write_unsafe(int column, int row, bool value) {
			int index = this->index_from_column_and_row(column,row);
			this->start_of_binary_map[index] = value;
		}

		bool* start_of_binary_map;
		int map_size;
		int height;
		int width;

	public:
		BinaryMap(int width, int height) {

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

		void print() {
			for(int i = 0; i < this->map_size; i++) {
				bool is_divisible = (i % width) == 0;
				if (is_divisible) {
					std::cout << "\n";
				}

				std::cout << this->start_of_binary_map[i];
			}
			std::cout << '\n';
		}
		
		void check_case_one(int x0, int y0, int x1, int y1) {
			this->check_bounds(x0, y0);
			this->check_bounds(x1, y1);

			if (x0 > x1) {
				throw std::invalid_argument("x0 > x1");
			}		

			if (y0 > y1) {
				throw std::invalid_argument("y0 > y1");
			}		

			int width = x1 - x0;
			int height = y1 - y0;
			
			if (height > width) {
				throw std::invalid_argument("height > width");
			}		
		}
		
		void draw_increment_drive_x(int x0, int y0, int x1, int y1) {
			this->check_case_one(x0, y0, x1, y1);

			int delta_x = (x1-x0);
			int delta_y = (y1-y0);
			int row = y0;
			int epsilon_flat = delta_y-delta_x;

			for (int column = x0; column <= x1; column++) {
				this->write_unsafe(column, row, 1); //It can be "unsafe" because bounds are already checked.

				if( epsilon_flat >= 0) {
					row+=1;
					epsilon_flat-=delta_x;
				}
				epsilon_flat += delta_y;
			}
		}	


		void draw_increment_drive_y(int x0, int y0, int x1, int y1) {
			int delta_x = (x1-x0);
			int delta_y = (y1-y0);

			int column = x0;
			int epsilon_flat = delta_x-delta_y;

			for (int row = y0; row <= y1; row++) {
				this->write_unsafe(column, row, 1); //It can be "unsafe" because bounds are already checked.

				if( epsilon_flat >= 0) {
					column+=1;
					epsilon_flat-=delta_y;
				}
				epsilon_flat += delta_x;
			}
		}	

		void draw_decrement_drive_y(int x0, int y0, int x1, int y1) {
			int delta_x = abs(x1-x0); 
			int delta_y = abs(y1-y0);  

			int column = x0;
			int epsilon_flat = delta_x-delta_y;



			for (int row = y0; row >= y1; row--) {
				this->write_unsafe(column, row, 1); //It can be "unsafe" because bounds are already checked.

				if (epsilon_flat >= 0) {
					column+=1;
					epsilon_flat-=delta_y;
				}

				epsilon_flat += delta_x;
			}
		}	

		void draw_decrement_drive_x(int x0, int y0, int x1, int y1) {
			int delta_x = abs(x1-x0); 
			int delta_y = abs(y1-y0);  

			int row = y0;
			int epsilon_flat = delta_y-delta_x;

			for (int column = x0; column <= x1; column++) {
				this->write_unsafe(column, row, 1); //It can be "unsafe" because bounds are already checked.

				if (epsilon_flat >= 0) {
					row-=1;
					epsilon_flat-=delta_x;
				}

				epsilon_flat += delta_y;
			}
		}	
		
		void drive_x(int x0, int y0, int x1, int y1) {
			if (y0 > y1) {
				draw_decrement_drive_x(x0, y0, x1, y1);
			} else {
				draw_increment_drive_x(x0, y0, x1, y1);
			}
		}

		void drive_y(int x0, int y0, int x1, int y1) {
			if (y0 > y1) {
				draw_decrement_drive_y(x0, y0, x1, y1);
			} else {
				draw_increment_drive_y(x0, y0, x1, y1);
			}
		}
		

		void draw_general(int x0, int y0, int x1, int y1) {
			int delta_x = abs(x0-x1);
			int delta_y = abs(y0-y1);

			int left_x;
			int left_y;
			int right_x;
			int right_y;

			if (x0 > x1) {
				left_x = x1;	
				right_x = x0;	
				left_y = y1;	
				right_y = y0;	
			} else {
				left_x = x0;	
				right_x = x1;	
				left_y = y0;	
				right_y = y1;	
			}

			if (delta_y > delta_x) {
				drive_y(left_x, left_y, right_x, right_y);
			} else {
				drive_x(left_x, left_y, right_x, right_y);
			}
		}

		//void draw_all_cases(int x0, int y0, int x1, int y1) {
		//	int delta_x = x1-x0;
		//	int delta_y = (y1-y0);

		//	if (delta_x*delta_y < 0) { // either delta_x < 0 or delta_y < 0 but not both.

		//}	
		//}
};

int main() {
	auto map = BinaryMap(20,20);
	map.draw_general(0,0,19,8);
	map.print();
}
