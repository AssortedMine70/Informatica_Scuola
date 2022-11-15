import java.util.Random;

public class MEG {
	int[][] matrix;
	
	public MEG(int n, int bound) {
		this.matrix = new int[n][n];
		Random r = new Random();
		
		for(int i = 0; i<matrix.length; ++i)
			for(int j = 0; j<matrix[i].length; ++j)
				if(i<j)
					matrix[i][j] = r.nextInt(bound);
	}

	@Override
	public String toString() {
		StringBuilder str = new StringBuilder();
		for(int i = 0; i<matrix.length; ++i) {
			for(int j = 0; j<matrix[i].length; ++j)
				str.append(matrix[i][j] + " ");
			str.append("\n");
		}
		return str.toString();
	}
}
