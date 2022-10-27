import java.util.Arrays;
import java.util.Random;

public class Tris {
	private int[][] field;
	private int player;
	
	public Tris() {
		player = new Random().nextInt(2)+1;
		field = new int[3][3];
		for (int i = 0; i < field.length; i++) {
			for (int j = 0; j < field.length; j++) {
				field[i][j] = 0;
			}
		}
	}
	
	public void set(int x, int y) {
		if(field[y][x]==0) {
			field[y][x] = player;
			player = player == 1 ? 2 : 1;
			check();
		}
	}
	
	public boolean check() {
		return false;
	}

	@Override
	public String toString() {
		return "Field [field=" + Arrays.toString(field[0]) + Arrays.toString(field[1]) + Arrays.toString(field[2]) + "]";
	}
}
