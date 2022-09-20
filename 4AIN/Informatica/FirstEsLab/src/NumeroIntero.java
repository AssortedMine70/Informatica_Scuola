/**
 * @author Federico Santucci
 */
public class NumeroIntero {
	private Integer i;
	
	/**
	 * NumeroIntero
	 * @paraminizializza il valore su cui lavora l'oggetto a null
	 */
	public NumeroIntero() {
		i = null;
	}
	
	/**
	 * NumeroIntero
	 * @param inizializza il valore su cui lavora l'oggetto direttamente alla dichiarazione
	 */
	public NumeroIntero(Integer n) {
		this.i = n;
	}
	
	/**
	 * isEven
	 * @return risultato del controllo
	 */
	public Boolean isEven() {
		return i!=null ? i % 2 == 0 : null;
	}
	
	/**
	 * setValue
	 * @param imposta il valore su cui lavora l'oggetto
	 */
	public void setValue(Integer n) {
		this.i = n;
	}
}
