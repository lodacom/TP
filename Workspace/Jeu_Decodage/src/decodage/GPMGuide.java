package decodage;

public class GPMGuide extends AbstractGestPhraseMystere
{
	AlphabetSymbole alphaCode;
	AlphabetLettre alpha;
	String symbolesUtilisateur[];
	
	public GPMGuide(AlphabetSymbole p_alphaCode,AlphabetLettre p_alpha)
	{
		this.alphaCode=p_alphaCode;
		this.alpha=p_alpha;
		this.symbolesUtilisateur=new String [26];
	}
	
	public String Suite_Mot_Decodage(String p_phrase) 
	{
		// TODO Auto-generated method stub
		String phrase_courante="";
		for (int i=0;i<p_phrase.length();i++)
		{
			String charac=p_phrase.substring(i, i+1);//compris entre a et z
			int index=alpha.getIndexLettre(charac);
			String symb=this.symbolesUtilisateur[index];
			phrase_courante+=symb;
		}
		return phrase_courante;
	}

	public void Association_Lettre_Symbole(String p_lettre,String p_symbole) 
	{
		// TODO Auto-generated method stub
		int index=alpha.getIndexLettre(p_lettre);
		this.symbolesUtilisateur[index]=p_symbole;
	}
	
	/**
	 * @param lettre
	 * @param symbole
	 * @return vrai s'il y a une bonne association sinon retourne faux.
	 */
	public boolean Bonne_Association(String lettre,String symbole)
	{
		int index_lettre=this.alpha.getIndexLettre(lettre);
		int index_symb=this.alphaCode.getIndexSymbole(symbole);
		return (index_lettre==index_symb);	
	}

}
