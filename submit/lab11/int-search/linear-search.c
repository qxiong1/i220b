/** Return index of element in a[nElements]; < 0 if not found. */
int
search_for_element(int a[], int nElements, int element)
{
  int i;
  int index = -1;
  for(i=0 ; i<nElements ; i++)
  {
  	if(a[i] == element)
	{
		index = i;
		break;
	}
  }

  return index;
	//@TODO add your code here to meet above spec.
}
