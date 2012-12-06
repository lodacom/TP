package seminaire;

import java.util.Scanner;

public class EPlanification extends EtatSeminaire
{

	public EPlanification(CycleSeminaires p_cycle) 
	{
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		Scanner sc=new Scanner(System.in);
		
		System.out.print("Saisissez le titre du séminaire\n");	
		String titre=sc.nextLine();
		
		System.out.print("Saisissez un résumé du séminaire\n");
		String resu=sc.nextLine();
		
		System.out.print("Saisissez le nombre maximum de participants\n");
		int capa=sc.nextInt();
		
		System.out.println("Saissez le temps que va durer le séminaire en milliseconde");
		int temps=sc.nextInt();
		
		Creneau cren=new Creneau(temps);
		this.cycle.setCreneau(cren);
		this.cycle.setTitre(titre);
		this.cycle.setResume(resu);
		this.cycle.setCapacite(capa);
		return 1;//prochain état (vers EPlaceDispo)
	}

}
