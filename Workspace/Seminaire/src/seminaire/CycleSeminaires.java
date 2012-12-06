package seminaire;

import java.util.ArrayList;

public class CycleSeminaires 
{
	private String titre;
	private String resume;
	private int nbInscrits;
	private int capacite;
	protected EtatSeminaire etatCourant;
	protected EtatSeminaire[] etats= new EtatSeminaire[9];
	public ArrayList<Adherent> listeInscrit;
	public ArrayList<Adherent> listeAttente;
	public Creneau cren;
	
	public CycleSeminaires(String p_titre,String p_resume)
	{
		this.titre=p_titre;
		this.resume=p_resume;
		
		listeInscrit=new ArrayList<Adherent>();//cr�ation des listes ne pas oublier
		listeAttente=new ArrayList<Adherent>();
		
		this.etats[0]=new EPlanification(this);
		this.etats[1]=new EPlaceDispo(this);
		this.etats[2]=new EComplet(this);
		this.etats[3]=new EPreparationSeminaire(this);
		this.etats[4]=new EEnCours(this);
		this.etats[5]=new ETermine(this);
		this.etats[6]=new EAbandonne(this);
		this.etats[7]=new EAnnule(this);
		this.etats[8]=new EArchive(this);
		
		this.etatCourant=this.etats[0];//initialisation de l'�tat de d�part
	}
	
	public int enter(Adherent ad)
	{
		int cptEtat = this.etatCourant.enter(ad) ;//on garde la valeur du nouvel �tat
		this.etatCourant=this.etats[cptEtat];//mis � jour de l'�tat
		System.out.println("Je suis dans l'�tat num�ro: " + cptEtat);
		System.out.println("Etape suivante...");
		return cptEtat;//ex�cution du prochain �tat
	}
	
	public void ajoutListeAttente(Adherent ad)
	{
		this.listeAttente.add(ad);
	}

	public Adherent popListeAttente()
	{
		Adherent ad=this.listeAttente.get(0);//on prend le premier
		this.listeAttente.remove(ad);
		this.listeInscrit.add(ad);//on le met dans la liste d'inscrit
		return ad;
	}
	
	public void inscription(Adherent ad)
	{		
		this.listeInscrit.add(ad);
		this.nbInscrits++;
		System.out.println("Votre inscription a �t� effectu�e");
	}
	
	public void desistement(Adherent ad)
	{
		this.listeInscrit.remove(ad);
		this.nbInscrits--;
	}
	
	public void archiver()
	{
		System.out.println("Votre s�minaire a �t� archiv�");
	}

	public int getNbInscrits() {
		return nbInscrits;
	}
	
	public int getCapacite() {
		return capacite;
	}

	public Creneau getCreneau(){
		return cren;
	}
	
	public ArrayList<Adherent> getListeInscrit() {
		return listeInscrit;
	}

	public ArrayList<Adherent> getListeAttente() {
		return listeAttente;
	}

	public void setTitre(String titre) {
		this.titre = titre;
	}

	public void setResume(String resume) {
		this.resume = resume;
	}

	public void setCapacite(int capacite) {
		this.capacite = capacite;
	}
	
	public void setCreneau(Creneau p_cren){
		this.cren=p_cren;
	}
	
}
