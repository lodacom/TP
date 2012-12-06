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
	
	public String Suite_Mot_Decodage() 
	{
		// TODO Auto-generated method stub
		return null;
	}

	public void Association_Lettre_Symbole() 
	{
		// TODO Auto-generated method stub
		
	}
	
	/**
	 * @param lettre
	 * @param symbole
	 * @return vrai s'il y a une bonne association sinon retourn faux
	 */
	public boolean Bonne_Association(String lettre,String symbole)
	{
		int index_lettre=this.alpha.getIndexLettre(lettre);
		int index_symb=this.alphaCode.getIndexSymbole(symbole);
		return (index_lettre==index_symb);	
	}

}
