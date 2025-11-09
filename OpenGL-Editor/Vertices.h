#pragma once

inline float squareVertices[] = {
  //Koordinaten			//Farbe
   -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,

   -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};

inline float triangleVertices[] = {
   -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
};

inline float pyramidVertices[] = {
    // --- Seitenflächen ---
    // Front
     0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,   // Spitze (rot)
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   // Links unten (grün)
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   // Rechts unten (blau)

     // Rechts
      0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,

      // Hinten
       0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,

      // Links
       0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,

      // --- Boden (Quadrat) ---
      -0.5f, -0.5f,  0.5f,   0.2f, 0.2f, 0.2f,
       0.5f, -0.5f,  0.5f,   0.2f, 0.2f, 0.2f,
       0.5f, -0.5f, -0.5f,   0.2f, 0.2f, 0.2f,
      -0.5f, -0.5f, -0.5f,   0.2f, 0.2f, 0.2f
};
