package bidon;

import java.util.ArrayList;
import java.util.Scanner;

public class Jeu 
{
	public ArrayList<Commande> ListeCommande;
	public ArrayList<Bidon> ListeBidon;
	
	public Jeu()
	{
		this.ListeCommande=new ArrayList<Commande>();
		this.ListeBidon=new ArrayList<Bidon>();
	}
	
	public void jouer()
	{
		int action=this.action();
		Bidon bid=this.demandeChoixBidon();
		switch(action)
		{
			case 1:bid.remplir();
			break;
			case 2:bid.vider();
			break;
			case 3:;
			break;
			default: System.out.println("Cette action n'existe pas connard");
			break;
		}
	}
	
	public Bidon rechercherBidon(String p_nom)
	{
		int i=0;
		while (i<this.ListeBidon.size() && this.ListeBidon.get(i).getNom().equalsIgnoreCase(p_nom))
		{
			i++;
		}
		if (i<this.ListeBidon.size())
		{
			return this.ListeBidon.get(i);
		}
		else
		{
			return null;
		}
	}
	
	public int action()
	{
		System.out.println("Saisissez l'action que vous voulez effectuer:");
		System.out.println("1:Remplir");
		System.out.println("2:Vider");
		System.out.println("3:Transvaser");
		Scanner sc=new Scanner(System.in);
		int action = sc.nextInt();
		return action;
	}
	
	public Bidon demandeChoixBidon()
	{
		System.out.println("Saisissez le bidon sur lequel vous voulez faire l'action");
		Scanner sc=new Scanner(System.in);
		String choix = sc.nextLine();
		return this.rechercherBidon(choix);
	}
}
