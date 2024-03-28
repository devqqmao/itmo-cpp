#!/usr/bin/awk -f

# Usage:
#     compare_matrices.awk reference_matrix.txt other_matrix.txt

BEGIN {
  # Set record separator to read all file as single line
  RS="";
  #FS=" |\n";
  mat1_len=0;
  mat2_len=0;
}

{
  # NR - total number of processed records
  # FNR - number of processed records in current file
  if (NR == FNR)
  {
    # Save first matrix
    for (i = 1; i <= NF; i++) # NF - number of fields
    {
      if (!($i ~ "^[ \r\n]*$"))
      {
        mat1[mat1_len] = $i;
        #print "mat1[" mat1_len "]=" mat1[mat1_len];
        mat1_len++;
      }
    }
  }
  else
  {
    # Save second matrix
    for (i = 1; i <= NF; i++)
    {
      if (!($i ~ "^[ \r\n]*$"))
      {
        mat2[mat2_len] = $i;
        #print "mat2[" mat2_len "]=" mat2[mat2_len];
        mat2_len++;
      }
    }
  }
}

END {
  eps = 1e-4;

  if (mat1_len != mat2_len)
  {
    print "Wrong number of words in file (" mat1_len "!=" mat2_len ")";
    exit 1;
  }

  # mat1 is considered reference for relative error
  r_ref = mat1[0];
  c_ref = mat1[1];
  r_check = mat2[0];
  c_check = mat2[1];
  if (r_ref != r_check || c_ref != c_check)
  {
    print "Matrices sizes don't match: (" r_ref "," c_ref ")!=(" r_check "," c_check ")";
    exit 1;
  }

  for (i = 2; i < mat1_len; i++)
  {
    v_ref = mat1[i]
    v_check = mat2[i]
    diff = v_ref - v_check;
    if (diff < 0)
    {
      diff = -diff;
    }

    if (diff == 0)
    {
      continue;
    }

    rel_error = diff / (v_ref == 0 ? 1 : v_ref);
    if (rel_error < 0)
    {
      rel_error = -rel_error;
    }
    if (rel_error < eps)
    {
      continue;
    }

    print "Mismatch at word " i ": " v_ref "!=" v_check;
    exit 1;
  }
}
