# 🌍 FDF - Fil De Fer

## 📝 Présentation

**FDF** est un projet de **visualisation 3D en fil de fer** permettant de représenter un **terrain en relief** à partir d’un fichier `.fdf` contenant des coordonnées en **3D**.  
L’objectif est de manipuler la **MiniLibX**, de comprendre la **projection isométrique**, et d’implémenter un rendu graphique interactif.

Ce projet met l’accent sur la **programmation graphique**, la **manipulation des matrices**, et l’**optimisation des affichages en 2D**.

---

## 🛠️ Fonctionnalités

### ✅ Partie Obligatoire :
- **Lecture et parsing d’un fichier `.fdf`** contenant les données d’un terrain.
- **Affichage des points en 3D** en utilisant une **projection isométrique**.
- **Connexion des points par des segments** pour créer un **effet fil de fer**.
- **Gestion des couleurs** pour représenter la profondeur et le relief.
- **Affichage fluide** via la **MiniLibX** (création de fenêtres, gestion des images).
- **Gestion des événements clavier et souris** :
  - `ESC` : Quitter proprement le programme.
  - `↑ ↓ ← →` : Déplacement du terrain.
  - `+ / -` : Zoom avant/arrière.
  - `R` : Reset de la vue.
- **Optimisation des calculs** pour un affichage fluide.

### 🎯 Bonus :
- **Rotation de la carte en temps réel**.
- **Zoom progressif et fluide**.
- **Gestion améliorée des couleurs en dégradé** selon la hauteur des points.

---

## 📌 Technologies Utilisées

- **C (Norminette respectée)**
- **MiniLibX** (gestion de la fenêtre et affichage graphique)
- **Mathématiques appliquées** (Matrices, Transformations, Trigonométrie)
- **Manipulation avancée des fichiers (`open`, `read`, `close`)**
- **Gestion des événements (`mlx_key_hook`, `mlx_mouse_hook`)**

---

## 🏗️ Structure du Projet

📂 headers  
┣ 📜 fdf.h  
┣ 📜 fdf_bonus.h  
┣ 📜 libft.h  
┗ 📜 mlx.h  

📂 libft  

📂 maps  

📂 minilibx  

📂 srcs  
┣ 📂 dots  
  ┣ 📜 dots.c  
  ┣ 📜 dots_brain.c  
  ┗ 📜 dots_utils.c  
┣ 📂 dots_bonus  
  ┣ 📜 dots_bonus.c  
  ┣ 📜 dots_brain_bonus.c  
  ┗ 📜 dots_utils_bonus.c  
┣ 📂 mooves  
  ┗ 📜 mooves_brain.c  
📂 mooves_bonus  
  ┣ 📜 mooves_bonus.c  
  ┣ 📜 mooves_brain_bonus.c  
  ┗ 📜 mooves_utils_bonus.c  
┣ 📂 parsing  
  ┣ 📜 parsing_brain.c  
  ┣ 📜 parsing_utils_1.c  
  ┗ 📜 parsing_utils_2.c  
┣ 📂 pixel  
  ┣ 📜 pixel_brain.c  
  ┣ 📜 pixel_draw.c  
  ┗ 📜 pixel_utils.c  
┣ 📂 pixel_bonus  
  ┣ 📜 fdf.c  
  ┗ 📜 fdf_bonus.c  

📜 Makefile  

---

## 🔥 Difficultés Rencontrées

- **Projection isométrique** : Calcul des transformations 3D → 2D pour un rendu réaliste.  
- **Gestion efficace des couleurs et du relief** pour améliorer l’esthétique.  
- **Optimisation des performances** pour éviter les ralentissements dans le rendu graphique.  
- **Implémentation propre des événements utilisateurs (`key_hook`, `mouse_hook`)**.  
- **Manipulation avancée des fichiers pour extraire et afficher correctement les données**.  

---

## 🏗️ Mise en place

1. **Cloner le dépôt** :  
   ```bash
   git clone https://github.com/ton-repo/fdf.git
   cd fdf
2. **Compiler le projet** :
   ```bash
   make
3. **Lancer le programme avec un fichier .fd** :
   ```bash
   ./fdf maps/42.fdf
4. **Nettoyer les fichiers compilés** :
   ```bash
   make clean
   make fclean

---

## 👨‍💻 Équipe  

👤 Grégoire Chamorel (Gchamore)  

---

## 📜 Projet réalisé dans le cadre du cursus 42.  

Tu peux bien sûr modifier ce README selon tes besoins, ajouter plus de détails sur ton approche et des instructions d’installation précises. 🚀  
