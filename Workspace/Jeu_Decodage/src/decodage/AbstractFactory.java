package decodage;

/**
 * <pre>
 * Cette classe permet de mettre en place différent niveaux de jeu.
 * Ces différents niveaux héritent de cette même classe.
 * Niveaux: Facile, Moyen, Difficile
 * </pre>
 * @author Lolo
 */
public abstract class AbstractFactory 
{
	public String lettres[];
	public abstract AbstractAlphabet CreateAlphabet();
	public abstract AbstractGestPhraseMystere CreateGPM();
	public abstract String encode(String enc);
	/**
	 * @param phrase
	 * @return les lettres de la phrase sans doublons
	 */
	public String[] Lettres_Phrase(String phrase)
	{
		this.lettres=new String[26];//tableau de 26 lettres
		for (int i=0;i<phrase.length();i++)
		{
			String charac=phrase.substring(i, i+1);//compris entre a et z
			char inter=charac.charAt(0);
			if (inter!=' ')
			{
				int place=(int) inter;
				//System.out.println(charac+","+place);
				place=place - 97;//on obtient l'index où on doit le placer
				this.lettres[place]=charac;
			}
		}
		return this.lettres;
	}
	
	/**
	 * @return le nombre de lettres dans la phrase sans compter
	 * les doublons
	 */
	public int Nbr_Lettres()
	{
		int cpt=0;
		for (int i=0;i<this.lettres.length;i++)
		{
			if (this.lettres[i]!=null)
			{
				cpt++;
			}
		}
		return cpt;//nombre total de lettres dans la phrase
	}
}
