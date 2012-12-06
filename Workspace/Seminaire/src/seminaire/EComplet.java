package seminaire;

import java.util.ArrayList;
import java.util.Scanner;

public class EComplet extends EtatSeminaire
{

	public EComplet(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		Scanner sc=new Scanner(System.in);
		ArrayList<Adherent> listeInscritTemp=this.cycle.getListeInscrit();
		for(int i=0;i<listeInscritTemp.size();i++)
		{
			System.out.println("Voulez-vous vous desister? "+listeInscritTemp.get(i).nom+" "+listeInscritTemp.get(i).prenom);
			System.out.print("Saisissez votre réponse\n");	
			String rep=sc.nextLine();
			if(rep.equals("oui"))
			{
				this.cycle.desistement(listeInscritTemp.get(i));
			}
		}
		
		if (this.cycle.getNbInscrits()<this.cycle.getCapacite())
		{
			if (!this.cycle.getListeAttente().isEmpty())
			{
				this.cycle.popListeAttente();
			}
		}
		
		System.out.println("Voulez-vous cloturez la reservation?");
		String rep2=sc.nextLine();
		if(rep2.equals("oui"))
		{
			if (this.cycle.getNbInscrits()>1)//dans l'énoncé c'est 10
			{
				System.out.println("Allons préparer le séminaire");
				return 3;//vers l'état EPreparationSeminaire
			}
			else
			{
				System.out.println("Le nombre de participant n'est pas suffisant: "+this.cycle.getNbInscrits());
				return 7;//vers l'état EAnnule
			}
		}
		else
		{
			if(this.cycle.getNbInscrits()>=this.cycle.getCapacite())
			{
				this.cycle.ajoutListeAttente(this.demandeInfo());
				System.out.println("Vous avez été mis sur la liste d'attente");
				return 2;//on revient dans EComplet
			}
			else
			{	
				return 1;//vers l'état EPlaceDispo
			}
		}
	}

}
