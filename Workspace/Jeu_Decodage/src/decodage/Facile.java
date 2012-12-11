package decodage;

import java.util.Random;

/**
 * <pre>
 * Classe équivalent à Concrete Factory dans le pattern Abstract Factory.
 * Ici on construit le niveau Facile
 * </pre>
 */
public class Facile extends AbstractFactory
{
	AlphabetSymbole alphaCode;
	AlphabetLettre alpha;
	//AbstractAlphabet abstr;
	
	public Facile(AlphabetSymbole p_alphaCode,AlphabetLettre p_alpha)
	{
		this.alphaCode=p_alphaCode;
		this.alpha=p_alpha;
		this.alpha.init_tableau();//initialisation du tableau de lettres
		this.alphaCode.init_tableau();//initialisation de symboles
	}
	
	@Override
	public AbstractAlphabet CreateAlphabet() 
	{
		// TODO Auto-generated method stub
		/*Que faut-il mettre?
		 * abstr=?
		 */
		return null;
	}

	@Override
	public AbstractGestPhraseMystere CreateGPM() 
	{
		// TODO Auto-generated method
		//idem que faut-il mettre?
		return null;
	}
	
	/**
	 * @return la phrase encodée
	 */
	public String encode(String phrase)
	{
		String phrase_encode="";
		String lettres[];
		lettres=this.choix_lettres_encodees(phrase);//les lettres que l'on va encoder
		for (int i=0;i<phrase.length();i++)
		{
			String charac=phrase.substring(i, i+1);//récupération car par car
			//System.out.println("Le charactère pris est: "+charac);
			if (charac.equals(" "))
			{
				phrase_encode+=" ";//on concatène l'espace
			}
			else
			{
				int j=0;
				while(j<lettres.length && !lettres[j].equals(charac))
				{
					j++;
				}
				if (j<lettres.length)
				{
					//il faut encoder la lettre trouvée
					int index=alpha.getIndexLettre(charac);
					//System.out.println("L'index trouvé est: "+index);
					String encode=this.alphaCode.getSymbole(index);
					
					phrase_encode+=encode;//on concatène le caractère encodé
				}
				else
				{
					phrase_encode+=charac;//on n'encode pas le charactère
				}
			}
		}
		return phrase_encode;//phrase encodée :)
	}
	
	/**
	 * @param phrase
	 * @return les lettres qu'il faut encoder
	 */
	int remplissage[];
	private String[] choix_lettres_encodees(String phrase)
	{
		String lettre_phrase[];
		lettre_phrase=new String[26];
		lettre_phrase=this.Lettres_Phrase(phrase);
		int nbr_lettres=this.Nbr_Lettres();
		//récupération du nombre de lettres sans compter les doublons
		String reduit_lettre[];
		reduit_lettre=new String[nbr_lettres];
		//récupération de toutes les lettres de la phrase sans les doublons
		int j=0;
		for (int i=0;i<lettre_phrase.length;i++)
		{
			if (lettre_phrase[i]!=null)
			{
				reduit_lettre[j]=lettre_phrase[i];
				j++;
				//on transfert dans un plus petit tableau
			}
		}
		int nbr_lettres_encode=(int) Math.floor(nbr_lettres * 0.7);
		String lettres_encodees[];
		lettres_encodees=new String[nbr_lettres_encode];
		remplissage=new int[nbr_lettres_encode];
		int index=0;
		for (int i=0;i<lettres_encodees.length;i++)
		{
			index=this.choix_lettre_encode(nbr_lettres_encode,i);
			//System.out.print(index);
			lettres_encodees[i]=reduit_lettre[index];
			System.out.print(reduit_lettre[i]);
			//index choisit au hazard 
		}
		return lettres_encodees;
	}
	
	/**
	 * @param nbr_lettres_encode
	 * @param remplissage
	 * @param index
	 * @return l'index qu'il faut prendre dans le tableau réduit de lettres
	 */
	Random r=new Random();
	private int choix_lettre_encode(int nbr_lettres_encode,int index)
	{
		int val=r.nextInt(nbr_lettres_encode+1);//on va choisir l'index au hazard
		int i=0;
		while (i<remplissage.length && remplissage[i]!=val)
		{
			i++;
		}
		if (i<remplissage.length)
		{
			return this.choix_lettre_encode(nbr_lettres_encode,index);
		}
		else
		{
			remplissage[index]=val;
			return val;
		}
	}

}