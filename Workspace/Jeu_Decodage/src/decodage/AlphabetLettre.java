package decodage;
/**
 * Cette classe est l'équivalent à Concrete Porduct dans le pattern 
 * Abstract Factory et construit l'aphabet Français
 * @author Lolo 
 */
public class AlphabetLettre extends AbstractAlphabet
{

	public String alphaLet[];
	
	/**
	 * Permet de construire le tableau qui contiendra l'alphabet
	 */
	public AlphabetLettre()
	{
		//initialise l'alphabet lettre
		this.alphaLet=new String[26];
		System.out.println("Instantiation de AlphabetLettre");
	}
	
	/**
	 * Initialise le tableau avec les lettres de l'alphabet
	 */
	public void init_tableau()
	{
		int cpt=97;
		for (int i=0;i<this.alphaLet.length;i++)
		{
			this.alphaLet[i]=new Character((char) cpt).toString();//transforme un int en String
			cpt++;
		}
	}
	
	/**
	 * @param lettre
	 * @return l'indice de la lettre passée en paramètre
	 */
	public int getIndexLettre(String lettre)
	{
		int i=0;
		while(i<this.alphaLet.length && !this.alphaLet[i].equals(lettre))
		{
			i++;
		}
		return i;
	}
}
