package decodage;

import java.util.Random;
/**
 * Cette classe est l'équivalent à Concrete Porduct dans le pattern 
 * Abstract Factory et construit l'aphabet encripté
 * @author Lolo
 */
public class AlphabetSymbole extends AbstractAlphabet
{
	public String alphaSymb[];
	private int verif[];
	private Random r=new Random();
	private int val;
	
	public AlphabetSymbole()
	{
		//initialise l'alphabet lettre
		this.alphaSymb=new String[26];
		this.verif=new int[26];
	}
	
	public void init_tableau()
	{
		for (int i=0;i<this.alphaSymb.length;i++)
		{
			this.choisir();
			this.verif[i]=val;//on met la valeur trouvée
			this.alphaSymb[i]=new Character((char) val).toString();
		}
		
	}
	
	public void inti_tableau_difficile()
	{
		for (int i=0;i<this.alphaSymb.length;i++)
		{
			this.choisirDifficile();
			this.verif[i]=val;//on met la valeur trouvée
			this.alphaSymb[i]=new Character((char) val).toString();
		}
	}
	
	/**
	 * @see http://www.table-ascii.com/ pour la table ascii
	 */
	public void choisir()
	{
		int j=0;
		this.val= 33 + r.nextInt(60 - 33);//renouvelement de la valeur
		//code ascii entre ! et ; 
		while (j<this.verif.length && this.verif[j]!=val)
		{
			 j++;
		}
		if (j<this.verif.length)
		{
			choisir();
			//il faut rechoisir
		}
	}
	
	public void choisirDifficile()
	{
		int j=0;
		this.val= 97 + r.nextInt(123 - 97);//renouvelement de la valeur
		//code ascii entre a et z
		while (j<this.verif.length && this.verif[j]!=val)
		{
			 j++;
		}
		if (j<this.verif.length)
		{
			choisirDifficile();
			//il faut rechoisir
		}
	}
	
	/**
	 * @param index
	 * @return la valeur de l'index du tableau de symbole
	 */
	public String getSymbole(int index)
	{
		//retourne le symbole à l'index index
		return this.alphaSymb[index];
	}
	
	public int getIndexSymbole(String symbole)
	{
		int i=0;
		while (i<this.alphaSymb.length && this.alphaSymb[i]!=symbole)
		{
			i++;
		}
		if (i<this.alphaSymb.length)
		{
			return i;
		}
		else
		{
			return -1;//erreur
		}
	}
}
