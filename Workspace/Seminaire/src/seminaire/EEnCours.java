package seminaire;

import java.util.ArrayList;
import java.util.Scanner;

public class EEnCours extends EtatSeminaire
{

	public EEnCours(CycleSeminaires p_cycle) {
		super(p_cycle);
		// TODO Auto-generated constructor stub
	}

	@Override
	int enter(Adherent ad) 
	{
		// TODO Auto-generated method stub
		Scanner sc=new Scanner(System.in);
		ArrayList<Adherent> listeInscritTemp=this.cycle.getListeInscrit();
		
		if (!this.cycle.getCreneau().debut.isRunning())
		{
			//le timer s'est fini
			System.out.println("Le temps imparti est �coul�");
			return 5;//vers l'�tat ETermine
		}
		else
		{
			if(listeInscritTemp.size()>0)//dans l'�nonc� c'est 5
			{
				for(int i=0;i<listeInscritTemp.size();i++)
				{
					System.out.println("Voulez-vous vous abandonnez? "+listeInscritTemp.get(i).nom+" "+listeInscritTemp.get(i).prenom);
					System.out.print("Saisissez votre r�ponse\n");	
					String rep=sc.nextLine();
					if(rep.equals("oui"))
					{
						this.cycle.desistement(listeInscritTemp.get(i));
					}
				}
				return 4;//vers l'�tat EEnCours
			}
			else
			{
				return 6;//vers l'�tat EAbandonne
			}
		}
	}

}
