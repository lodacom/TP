package seminaire;

public class EArchive extends EtatSeminaire
{

	public EArchive(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		System.out.println("Votre séminaire a été archivé");
		return 8;//vers l'état EArchive on a plus d'état suivant
	}

}
