package seminaire;

public class EAbandonne extends EtatSeminaire
{

	public EAbandonne(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		System.out.println("Le s�minaire a �t� abandonn�");
		return 8;//vers l'�tat EArchive
	}

}
