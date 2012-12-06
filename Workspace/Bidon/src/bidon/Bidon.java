package bidon;

public class Bidon 
{
	private int capacite;
	private int volume_present;
	private String nom;
	
	public Bidon(int p_capacite,String p_nom)
	{
		this.capacite=p_capacite;
		this.nom=p_nom;
		this.volume_present=0;
	}
	
	public void vider()
	{
		this.volume_present=0;//on vide complètement
	}
	
	public void remplir()
	{
		this.volume_present=this.capacite;//on remplit à fond
	}
	
	public void transvaser(Bidon bid)
	{
		
	}
	
	public int getVolume_present() {
		return volume_present;
	}

	public void setVolume_present(int volume_present) {
		this.volume_present = volume_present;
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public int getCapacite() {
		return capacite;
	}

	public void setCapacite(int capacite) {
		this.capacite = capacite;
	}

	public void retirer() {
		// TODO Auto-generated method stub
		
	}

	public void ajouter() {
		// TODO Auto-generated method stub
		
	}
	
	
}
