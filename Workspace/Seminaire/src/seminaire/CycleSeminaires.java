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
		
		listeInscrit=new ArrayList<Adherent>();//création des listes ne pas oublier
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
		
		this.etatCourant=this.etats[0];//initialisation de l'état de départ
	}
	
	public int enter(Adherent ad)
	{
		int cptEtat = this.etatCourant.enter(ad) ;//on garde la valeur du nouvel état
		this.etatCourant=this.etats[cptEtat];//mis à jour de l'état
		System.out.println("Je suis dans l'état numéro: " + cptEtat);
		System.out.println("Etape suivante...");
		return cptEtat;//exécution du prochain état
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
		System.out.println("Votre inscription a été effectuée");
	}
	
	public void desistement(Adherent ad)
	{
		this.listeInscrit.remove(ad);
		this.nbInscrits--;
	}
	
	public void archiver()
	{
		System.out.println("Votre séminaire a été archivé");
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
