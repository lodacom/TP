package seminaire;

public class EPlaceDispo extends EtatSeminaire 
{

	public EPlaceDispo(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		if(this.cycle.getNbInscrits()<this.cycle.getCapacite())
		{
			System.out.println("Inscrivez-vous!");
			this.cycle.inscription(this.demandeInfo());
			return 1;//vers l'Žtat EPlaceDispo	
		}
		else
		{
			return 2;//vers l'Žtat EComplet
		}
	}

}
