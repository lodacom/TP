package seminaire;

public class EAnnule extends EtatSeminaire
{

	public EAnnule(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		System.out.println("Le s�minaire a �t� annul�");
		return 8;//vers l'�tat EArchive
	}

}
