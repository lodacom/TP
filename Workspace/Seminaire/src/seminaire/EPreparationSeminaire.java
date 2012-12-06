package seminaire;

public class EPreparationSeminaire extends EtatSeminaire
{

	public EPreparationSeminaire(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		System.out.println("Démarrage du compte à rebours");
		this.cycle.getCreneau().debut.start();//on démarre le timer
		return 4;//vers l'état EEnCours
	}

}
