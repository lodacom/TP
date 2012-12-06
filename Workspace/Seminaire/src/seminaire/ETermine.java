package seminaire;

public class ETermine extends EtatSeminaire
{

	public ETermine(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		System.out.println("Le sminaire s'est termin");
		return 8;//vers l'tat EArchive
	}

}
