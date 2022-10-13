package parentheses;
/**
 * @author Federico Santucci
 */
public abstract class TemplateValori {
	private int a, b, c;
	
	protected abstract String lbracket();
	protected abstract String rbracket();
	
	@Override
	public final String toString() {
		return lbracket()+a+", "+b+", "+c+rbracket();
	}
}
