package dico;

public class SortedDictionary extends AbstractDictionary
{
	public SortedDictionary()
	{
		
	}
	
	public SortedDictionary(int p_taille)
	{
		this.taille=p_taille;
		this.key=new Object[this.taille];
		this.value=new Object[this.taille];
	}
	
	@Override
	int size()
	{
		return this.taille;
	}
	
	int indexOf(Comparable p_key) 
	{
		// TODO Auto-generated method stub
		/*return -1 if the key doesn't exist in the dictionary
		 * else return the index
		*/
		int existe=-1;
		this.sortByInsertion();//arrays are sorted
		
		boolean trouve=false;  
		int id=0;  
		int ifin=this.taille; 
		int im;
	  
		while(!trouve && ((ifin - id) > 1))
		{
			im = (id + ifin)/2;  //index of the middle
			trouve = (p_key.compareTo(this.key[im]) == 0);
			//we look if the searched value is at this index
			if(p_key.compareTo(this.key[im]) > 0) ifin = im;
			else id = im;
		}
	  

		if( p_key.compareTo(key[id])== 0) 
		{
			return id;  //if we have found the key return the index
		}
		else 
		{
			return existe;  //else return -1
		}  
	}

	@Override
	int newIndexOf(Object key) 
	{
		// TODO Auto-generated method stub
		/*return -1 if there is already the key
		 * else return the new size. Thus a new key 
		 * will be inserted.
		 */
		if (this.indexOf(key)==-1)
		{
			int i=0;
			while(i<this.taille && !this.key[i].equals(null))
			{//searching an available place
				i++;
			}
			if (i<this.taille)
			{
				return i;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	
	void sortByInsertion()
	{
	   int j;
	   for (int i = 1; i < this.taille; ++i) 
	   {
	       Comparable key = (Comparable) this.key[i];
	       Object value = this.value[i];

	       for (j = i; j > 0 && key.compareTo(this.key[j-1])>0; j--)
	       {
	           this.key[j] = this.key[j-1];//exchange of value of key
	           this.key[j-1] = key;
	           
	           this.value[j]=this.value[j-1];
	           this.value[j-1]=value;
	       }
	   }
	}

	@Override
	int indexOf(Object key) 
	{
		// TODO Auto-generated method stub
		return this.indexOf(key);
	}
}
