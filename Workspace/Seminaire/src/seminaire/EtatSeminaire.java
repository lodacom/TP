package seminaire;

import java.util.Scanner;

public abstract class EtatSeminaire 
{
	CycleSeminaires cycle;
	
	public EtatSeminaire(CycleSeminaires p_cycle)
	{
		this.cycle=p_cycle;
	}
	
	abstract int enter(Adherent ad);
	
	public Adherent demandeInfo()
	{
		Scanner sc=new Scanner(System.in);
		System.out.print("Saisissez votre nom\n");	
		String nom=sc.nextLine();
		
		System.out.print("Saisissez votre prénom\n");	
		String prenom=sc.nextLine();
		
		Adherent ad=new Adherent(nom,prenom);
		return ad;
	}
}
