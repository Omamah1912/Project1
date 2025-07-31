#!/usr/bin/env python3
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np

def create_sprite_pdf():
    """Create a comprehensive PDF document with all sprite specifications"""
    
    with PdfPages('Duck_Dash_Sprite_Reference.pdf') as pdf:
        
        # Page 1: Title and Overview
        fig, ax = plt.subplots(figsize=(8.5, 11))
        fig.suptitle('DUCK DASH - SPRITE REFERENCE GUIDE', fontsize=24, weight='bold', y=0.95)
        
        ax.text(0.5, 0.88, 'Version 2.0 - Complete Visual Design', fontsize=16, ha='center', 
                transform=ax.transAxes, style='italic', color='#666666')
        
        # Grid system explanation
        ax.text(0.05, 0.8, 'GRID SYSTEM & SIZING STANDARDS', fontsize=18, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        grid_info = [
            '• Base grid: 16×16 pixels (all sprites align to this grid)',
            '• Player Character: 32×32 pixels (2×2 grid units)',
            '• Environment Tiles: 32×32 pixels (standard tile size)',
            '• Small Collectibles: 16×16 pixels (1×1 grid unit)',
            '• Large Collectibles: 24×24 pixels (1.5×1.5 grid units)',
            '• Small Enemies: 24×24 pixels (1.5×1.5 grid units)',
            '• Large Enemies: 48×48 pixels (3×3 grid units)',
            '• UI Elements: 24×24 pixels (consistent UI sizing)'
        ]
        
        y_pos = 0.75
        for info in grid_info:
            ax.text(0.05, y_pos, info, fontsize=12, transform=ax.transAxes)
            y_pos -= 0.04
        
        # Color palette
        ax.text(0.05, 0.45, 'OFFICIAL COLOR PALETTE', fontsize=18, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        colors = [
            ('#87CEEB', 'Sky Blue', 'Background sky, water elements'),
            ('#32CD32', 'Grass Green', 'Ground tiles, vegetation'),
            ('#696969', 'Stone Gray', 'Platforms, rocks, obstacles'),
            ('#8B4513', 'Earth Brown', 'Ground, tree trunks, bears'),
            ('#FFD700', 'Golden Yellow', 'Player highlights, seeds, bees'),
            ('#FF4500', 'Danger Red', 'Enemies, hazards, UI alerts'),
            ('#9370DB', 'Magic Purple', 'Special effects, feathers'),
            ('#FFFFFF', 'Pure White', 'UI text, highlights, sparkles')
        ]
        
        y_pos = 0.4
        for color, name, usage in colors:
            # Color swatch
            rect = patches.Rectangle((0.05, y_pos-0.01), 0.03, 0.025, facecolor=color, 
                                   edgecolor='black', linewidth=1, transform=ax.transAxes)
            ax.add_patch(rect)
            ax.text(0.1, y_pos, f'{name}: {color}', fontsize=11, weight='bold', transform=ax.transAxes)
            ax.text(0.1, y_pos-0.02, f'Usage: {usage}', fontsize=9, color='#666666', transform=ax.transAxes)
            y_pos -= 0.06
        
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.axis('off')
        pdf.savefig(fig, bbox_inches='tight', dpi=300)
        plt.close()
        
        # Page 2: Player Sprites - Detailed
        fig, ax = plt.subplots(figsize=(8.5, 11))
        fig.suptitle('PLAYER SPRITES - ADVENTURER DUCK', fontsize=20, weight='bold', y=0.95)
        
        ax.text(0.5, 0.88, 'Size: 32×32 pixels | 8 Animation Frames Total', fontsize=14, 
                ha='center', transform=ax.transAxes, weight='bold', color='#2E4057')
        
        # Draw sprite frame grid
        frame_data = [
            ('Idle Frame 1', 0.15, 0.75, 'Breathing in'),
            ('Idle Frame 2', 0.35, 0.75, 'Breathing out'),
            ('Walk Frame 1', 0.55, 0.75, 'Left foot forward'),
            ('Walk Frame 2', 0.75, 0.75, 'Both feet together'),
            ('Walk Frame 3', 0.15, 0.55, 'Right foot forward'),
            ('Walk Frame 4', 0.35, 0.55, 'Both feet together'),
            ('Jump Frame 1', 0.55, 0.55, 'Takeoff pose'),
            ('Jump Frame 2', 0.75, 0.55, 'Landing pose')
        ]
        
        for label, x, y, description in frame_data:
            # Draw 32x32 pixel representation
            rect = patches.Rectangle((x-0.06, y-0.06), 0.12, 0.12, facecolor='#FFD700', 
                                   edgecolor='black', linewidth=2, transform=ax.transAxes)
            ax.add_patch(rect)
            
            # Add duck details
            # Body (yellow)
            body = patches.Ellipse((x, y), 0.08, 0.1, facecolor='#FFD700', 
                                 edgecolor='black', transform=ax.transAxes)
            ax.add_patch(body)
            
            # Hat (blue)
            hat = patches.Rectangle((x-0.03, y+0.03), 0.06, 0.03, facecolor='#4169E1', 
                                  edgecolor='black', transform=ax.transAxes)
            ax.add_patch(hat)
            
            # Beak (orange)
            beak = patches.Polygon([(x+0.04, y), (x+0.06, y+0.01), (x+0.06, y-0.01)], 
                                 facecolor='#FFA500', edgecolor='black', transform=ax.transAxes)
            ax.add_patch(beak)
            
            ax.text(x, y-0.1, label, fontsize=10, ha='center', weight='bold', transform=ax.transAxes)
            ax.text(x, y-0.13, description, fontsize=8, ha='center', style='italic', 
                   color='#666666', transform=ax.transAxes)
            ax.text(x, y-0.16, '32×32px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Animation timing details
        ax.text(0.05, 0.4, 'ANIMATION SPECIFICATIONS', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        anim_specs = [
            'IDLE ANIMATION:',
            '  • 2 frames (breathing cycle)',
            '  • 1.0 second total cycle time',
            '  • 0.5 seconds per frame',
            '  • Gentle up/down movement',
            '',
            'WALK ANIMATION:',
            '  • 4 frames (complete walk cycle)',
            '  • 0.4 second total cycle time',
            '  • 0.1 seconds per frame',
            '  • Classic side-scrolling movement',
            '',
            'JUMP ANIMATION:',
            '  • 2 frames (takeoff + landing)',
            '  • 0.2 seconds per frame',
            '  • Static poses (no cycling)',
            '',
            'VISUAL FEATURES:',
            '  • Bright yellow body with orange beak',
            '  • Blue adventure hat with feather detail',
            '  • Wing flapping animation during movement',
            '  • Sparkle effect when collecting items'
        ]
        
        y_pos = 0.35
        for spec in anim_specs:
            if spec.startswith('  •'):
                ax.text(0.08, y_pos, spec, fontsize=11, transform=ax.transAxes)
            elif spec.endswith(':'):
                ax.text(0.05, y_pos, spec, fontsize=12, weight='bold', transform=ax.transAxes)
            else:
                ax.text(0.05, y_pos, spec, fontsize=11, transform=ax.transAxes)
            y_pos -= 0.025
        
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.axis('off')
        pdf.savefig(fig, bbox_inches='tight', dpi=300)
        plt.close()
        
        # Page 3: Environment Sprites
        fig, ax = plt.subplots(figsize=(8.5, 11))
        fig.suptitle('ENVIRONMENT SPRITES', fontsize=20, weight='bold', y=0.95)
        
        # Grass tiles section
        ax.text(0.05, 0.88, 'GRASS TILES (32×32 pixels)', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        grass_variants = ['Base Grass', 'Flower Variant', 'Tall Grass', 'Dense Patch']
        for i, variant in enumerate(grass_variants):
            x = 0.15 + (i * 0.2)
            y = 0.78
            
            # Draw grass tile
            rect = patches.Rectangle((x-0.05, y-0.05), 0.1, 0.1, facecolor='#32CD32', 
                                   edgecolor='black', linewidth=2, transform=ax.transAxes)
            ax.add_patch(rect)
            
            # Add grass details
            for j in range(5):
                grass_x = x - 0.03 + (j * 0.015)
                grass_blade = patches.Rectangle((grass_x, y-0.04), 0.005, 0.06, 
                                              facecolor='#228B22', transform=ax.transAxes)
                ax.add_patch(grass_blade)
            
            ax.text(x, y-0.08, variant, fontsize=10, ha='center', weight='bold', transform=ax.transAxes)
            ax.text(x, y-0.11, '32×32px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Stone platforms section
        ax.text(0.05, 0.62, 'STONE PLATFORMS (32×32 pixels)', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        stone_types = ['Corner Block', 'Middle Block', 'Single Block']
        for i, stone_type in enumerate(stone_types):
            x = 0.2 + (i * 0.25)
            y = 0.52
            
            # Draw stone platform
            rect = patches.Rectangle((x-0.05, y-0.05), 0.1, 0.1, facecolor='#696969', 
                                   edgecolor='black', linewidth=2, transform=ax.transAxes)
            ax.add_patch(rect)
            
            # Add stone texture
            for j in range(3):
                for k in range(3):
                    dot_x = x - 0.03 + (j * 0.02)
                    dot_y = y - 0.03 + (k * 0.02)
                    dot = patches.Circle((dot_x, dot_y), 0.003, facecolor='#555555', 
                                       transform=ax.transAxes)
                    ax.add_patch(dot)
            
            ax.text(x, y-0.08, stone_type, fontsize=10, ha='center', weight='bold', transform=ax.transAxes)
            ax.text(x, y-0.11, '32×32px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Background elements section
        ax.text(0.05, 0.36, 'BACKGROUND ELEMENTS', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        # Clouds (64x32)
        x, y = 0.2, 0.26
        rect = patches.Rectangle((x-0.08, y-0.04), 0.16, 0.08, facecolor='#B0E0E6', 
                               edgecolor='black', linewidth=2, transform=ax.transAxes)
        ax.add_patch(rect)
        # Cloud shape
        cloud1 = patches.Circle((x-0.04, y), 0.03, facecolor='white', alpha=0.8, transform=ax.transAxes)
        cloud2 = patches.Circle((x, y), 0.035, facecolor='white', alpha=0.8, transform=ax.transAxes)
        cloud3 = patches.Circle((x+0.04, y), 0.03, facecolor='white', alpha=0.8, transform=ax.transAxes)
        ax.add_patch(cloud1)
        ax.add_patch(cloud2)
        ax.add_patch(cloud3)
        
        ax.text(x, y-0.08, 'Animated Clouds', fontsize=10, ha='center', weight='bold', transform=ax.transAxes)
        ax.text(x, y-0.11, '64×32px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Trees (48x64)
        x, y = 0.6, 0.22
        rect = patches.Rectangle((x-0.06, y-0.08), 0.12, 0.16, facecolor='#228B22', 
                               edgecolor='black', linewidth=2, transform=ax.transAxes)
        ax.add_patch(rect)
        # Tree trunk
        trunk = patches.Rectangle((x-0.01, y-0.08), 0.02, 0.06, facecolor='#8B4513', 
                                edgecolor='black', transform=ax.transAxes)
        ax.add_patch(trunk)
        # Tree foliage
        foliage = patches.Circle((x, y+0.02), 0.05, facecolor='#32CD32', 
                               edgecolor='black', transform=ax.transAxes)
        ax.add_patch(foliage)
        
        ax.text(x, y-0.12, 'Forest Trees', fontsize=10, ha='center', weight='bold', transform=ax.transAxes)
        ax.text(x, y-0.15, '48×64px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Environment notes
        ax.text(0.05, 0.08, 'ENVIRONMENT FEATURES:', fontsize=14, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        env_notes = [
            '• Grass tiles have 4 different variants for visual variety',
            '• Stone platforms include corner, middle, and single block types',
            '• Clouds drift slowly across the background (30-second cycle)',
            '• Trees have animated leaves that sway gently',
            '• All environment sprites use consistent lighting from top-left'
        ]
        
        y_pos = 0.05
        for note in env_notes:
            ax.text(0.05, y_pos, note, fontsize=11, transform=ax.transAxes)
            y_pos -= 0.025
        
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.axis('off')
        pdf.savefig(fig, bbox_inches='tight', dpi=300)
        plt.close()
        
        # Page 4: Collectible Sprites
        fig, ax = plt.subplots(figsize=(8.5, 11))
        fig.suptitle('COLLECTIBLE SPRITES', fontsize=20, weight='bold', y=0.95)
        
        collectibles = [
            ('MAGIC SEEDS', 16, 10, '#FFD700', 0.2, 0.8, 'Primary collectible with golden glow'),
            ('RAINBOW FEATHERS', 24, 50, '#9370DB', 0.5, 0.8, 'Special collectible with shimmer'),
            ('ENERGY POTIONS', 20, 25, '#87CEEB', 0.8, 0.8, 'Power-up with speed boost')
        ]
        
        for name, size, points, color, x, y, description in collectibles:
            # Title
            ax.text(x, y+0.1, name, fontsize=14, weight='bold', ha='center', 
                   transform=ax.transAxes, color='#2E4057')
            
            # Draw collectible
            scale = size / 32.0  # Scale relative to 32px
            rect_size = 0.1 * scale
            rect = patches.Rectangle((x-rect_size/2, y-rect_size/2), rect_size, rect_size, 
                                   facecolor=color, edgecolor='black', linewidth=2, 
                                   transform=ax.transAxes)
            ax.add_patch(rect)
            
            # Add specific details
            if 'SEEDS' in name:
                # Seed shape
                seed = patches.Ellipse((x, y), rect_size*0.6, rect_size*0.8, 
                                     facecolor='#FFD700', edgecolor='black', transform=ax.transAxes)
                ax.add_patch(seed)
                # Sparkle effect
                sparkles = [(x-0.02, y+0.02), (x+0.02, y-0.02), (x+0.015, y+0.015)]
                for sx, sy in sparkles:
                    sparkle = patches.RegularPolygon((sx, sy), 4, 0.005, orientation=np.pi/4,
                                                   facecolor='white', transform=ax.transAxes)
                    ax.add_patch(sparkle)
            
            elif 'FEATHERS' in name:
                # Feather shape
                feather = patches.Ellipse((x, y), rect_size*0.3, rect_size*0.9, 
                                        facecolor='#9370DB', edgecolor='black', transform=ax.transAxes)
                ax.add_patch(feather)
                # Rainbow stripes
                colors_rainbow = ['#FF0000', '#FFA500', '#FFFF00', '#00FF00', '#0000FF', '#8B00FF']
                for i, rainbow_color in enumerate(colors_rainbow):
                    stripe_y = y - rect_size*0.4 + (i * rect_size*0.15)
                    stripe = patches.Rectangle((x-rect_size*0.1, stripe_y), rect_size*0.2, rect_size*0.1,
                                             facecolor=rainbow_color, alpha=0.7, transform=ax.transAxes)
                    ax.add_patch(stripe)
            
            elif 'POTIONS' in name:
                # Bottle shape
                bottle = patches.Rectangle((x-rect_size*0.3, y-rect_size*0.4), rect_size*0.6, rect_size*0.8,
                                         facecolor='#87CEEB', edgecolor='black', transform=ax.transAxes)
                ax.add_patch(bottle)
                # Liquid inside
                liquid = patches.Rectangle((x-rect_size*0.25, y-rect_size*0.35), rect_size*0.5, rect_size*0.6,
                                         facecolor='#0000FF', alpha=0.6, transform=ax.transAxes)
                ax.add_patch(liquid)
                # Bubbles
                for i in range(3):
                    bubble_y = y - 0.02 + (i * 0.015)
                    bubble = patches.Circle((x, bubble_y), 0.003, facecolor='white', 
                                          alpha=0.8, transform=ax.transAxes)
                    ax.add_patch(bubble)
            
            # Details
            ax.text(x, y-0.08, f'{size}×{size} pixels', fontsize=10, ha='center', 
                   weight='bold', transform=ax.transAxes)
            ax.text(x, y-0.11, f'{points} points', fontsize=10, ha='center', 
                   color='#FF4500', weight='bold', transform=ax.transAxes)
            ax.text(x, y-0.14, description, fontsize=9, ha='center', 
                   style='italic', transform=ax.transAxes)
        
        # Animation specifications
        ax.text(0.05, 0.55, 'COLLECTIBLE ANIMATIONS', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        anim_details = [
            'MAGIC SEEDS:',
            '  • Gentle floating bob animation (2.0 second sine wave)',
            '  • Golden sparkle particles around the seed',
            '  • Soft "ding" sound on collection',
            '  • 0.5 second sparkle burst effect when collected',
            '',
            'RAINBOW FEATHERS:',
            '  • Slow rotation animation (3.0 second full rotation)',
            '  • Iridescent color shifting effect',
            '  • Magical chime sound on collection',
            '  • Rainbow particle trail when collected',
            '',
            'ENERGY POTIONS:',
            '  • Bubbling liquid animation inside bottle',
            '  • Gentle glow pulsing effect',
            '  • Power-up sound effect on collection',
            '  • Grants 5-second speed boost to player',
            '',
            'COLLECTION EFFECTS:',
            '  • All collectibles trigger golden sparkle burst',
            '  • Score popup appears showing points earned',
            '  • Brief screen flash for high-value items',
            '  • Particle effects match collectible colors'
        ]
        
        y_pos = 0.5
        for detail in anim_details:
            if detail.startswith('  •'):
                ax.text(0.08, y_pos, detail, fontsize=11, transform=ax.transAxes)
            elif detail.endswith(':'):
                ax.text(0.05, y_pos, detail, fontsize=12, weight='bold', transform=ax.transAxes)
            else:
                ax.text(0.05, y_pos, detail, fontsize=11, transform=ax.transAxes)
            y_pos -= 0.025
        
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.axis('off')
        pdf.savefig(fig, bbox_inches='tight', dpi=300)
        plt.close()
        
        # Page 5: Enemy Sprites
        fig, ax = plt.subplots(figsize=(8.5, 11))
        fig.suptitle('ENEMY SPRITES & HAZARDS', fontsize=20, weight='bold', y=0.95)
        
        # Bears section
        ax.text(0.05, 0.88, 'CARTOON BEARS (48×48 pixels)', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        bear_frames = ['Idle 1', 'Idle 2', 'Walk 1', 'Walk 2', 'Walk 3', 'Walk 4']
        for i, frame in enumerate(bear_frames):
            x = 0.12 + (i * 0.13)
            y = 0.78
            
            # Draw bear (48x48 = larger)
            rect = patches.Rectangle((x-0.06, y-0.06), 0.12, 0.12, facecolor='#8B4513', 
                                   edgecolor='black', linewidth=2, transform=ax.transAxes)
            ax.add_patch(rect)
            
            # Bear body
            body = patches.Ellipse((x, y-0.01), 0.08, 0.1, facecolor='#8B4513', 
                                 edgecolor='black', transform=ax.transAxes)
            ax.add_patch(body)
            
            # Bear head
            head = patches.Circle((x, y+0.03), 0.03, facecolor='#8B4513', 
                                edgecolor='black', transform=ax.transAxes)
            ax.add_patch(head)
            
            # Bear ears
            ear1 = patches.Circle((x-0.02, y+0.05), 0.01, facecolor='#8B4513', 
                                edgecolor='black', transform=ax.transAxes)
            ear2 = patches.Circle((x+0.02, y+0.05), 0.01, facecolor='#8B4513', 
                                edgecolor='black', transform=ax.transAxes)
            ax.add_patch(ear1)
            ax.add_patch(ear2)
            
            ax.text(x, y-0.09, frame, fontsize=9, ha='center', weight='bold', transform=ax.transAxes)
            ax.text(x, y-0.12, '48×48px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Bees section
        ax.text(0.05, 0.6, 'PIXEL BEES (24×24 pixels)', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        bee_frames = ['Wing Up', 'Wing Mid', 'Wing Down', 'Wing Mid']
        for i, frame in enumerate(bee_frames):
            x = 0.2 + (i * 0.2)
            y = 0.5
            
            # Draw bee (24x24 = medium)
            rect = patches.Rectangle((x-0.04, y-0.04), 0.08, 0.08, facecolor='#FFD700', 
                                   edgecolor='black', linewidth=2, transform=ax.transAxes)
            ax.add_patch(rect)
            
            # Bee body (yellow with black stripes)
            body = patches.Ellipse((x, y), 0.05, 0.06, facecolor='#FFD700', 
                                 edgecolor='black', transform=ax.transAxes)
            ax.add_patch(body)
            
            # Black stripes
            stripe1 = patches.Rectangle((x-0.02, y+0.01), 0.04, 0.01, facecolor='black', 
                                      transform=ax.transAxes)
            stripe2 = patches.Rectangle((x-0.02, y-0.01), 0.04, 0.01, facecolor='black', 
                                      transform=ax.transAxes)
            ax.add_patch(stripe1)
            ax.add_patch(stripe2)
            
            # Wings (position varies by frame)
            wing_offset = 0.02 if 'Up' in frame else 0.01 if 'Mid' in frame else 0
            wing1 = patches.Ellipse((x-0.025, y+wing_offset), 0.015, 0.03, facecolor='white', 
                                  alpha=0.7, edgecolor='black', transform=ax.transAxes)
            wing2 = patches.Ellipse((x+0.025, y+wing_offset), 0.015, 0.03, facecolor='white', 
                                  alpha=0.7, edgecolor='black', transform=ax.transAxes)
            ax.add_patch(wing1)
            ax.add_patch(wing2)
            
            ax.text(x, y-0.07, frame, fontsize=9, ha='center', weight='bold', transform=ax.transAxes)
            ax.text(x, y-0.1, '24×24px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Tornado section
        ax.text(0.05, 0.32, 'TORNADO HAZARD (64×96 pixels)', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        x, y = 0.25, 0.18
        # Draw tornado (64x96 = very large)
        rect = patches.Rectangle((x-0.08, y-0.12), 0.16, 0.24, facecolor='#696969', 
                               edgecolor='black', linewidth=2, transform=ax.transAxes)
        ax.add_patch(rect)
        
        # Tornado funnel shape
        tornado_points = [(x-0.06, y-0.12), (x+0.06, y-0.12), (x+0.02, y+0.12), (x-0.02, y+0.12)]
        tornado = patches.Polygon(tornado_points, facecolor='#696969', edgecolor='black', 
                                alpha=0.8, transform=ax.transAxes)
        ax.add_patch(tornado)
        
        # Debris particles
        debris_positions = [(x-0.04, y+0.08), (x+0.03, y+0.05), (x-0.01, y+0.1), 
                          (x+0.05, y+0.02), (x-0.03, y+0.03)]
        for dx, dy in debris_positions:
            debris = patches.Rectangle((dx, dy), 0.01, 0.01, facecolor='#8B4513', 
                                     alpha=0.6, transform=ax.transAxes)
            ax.add_patch(debris)
        
        ax.text(x, y-0.16, 'Spinning Tornado', fontsize=10, ha='center', weight='bold', transform=ax.transAxes)
        ax.text(x, y-0.19, '64×96px', fontsize=8, ha='center', transform=ax.transAxes)
        ax.text(x, y-0.22, '8 frames, very fast', fontsize=8, ha='center', style='italic', transform=ax.transAxes)
        
        # Enemy behavior notes
        ax.text(0.5, 0.32, 'ENEMY BEHAVIORS & STATS', fontsize=14, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        behavior_notes = [
            'BEARS:',
            '  • Patrol back and forth on platforms',
            '  • 0.8 second walk cycle (4 frames)',
            '  • Slow but persistent movement',
            '  • Deal 1 life point damage on contact',
            '  • Low growl sound effect',
            '',
            'BEES:',
            '  • Fly in sine wave patterns',
            '  • 0.2 second wing cycle (4 frames)',
            '  • Fast but predictable movement',
            '  • Deal 1 life point damage on contact',
            '  • High-pitched buzzing sound',
            '',
            'TORNADO:',
            '  • Moves in predictable patterns',
            '  • 0.1 second spin cycle (8 frames)',
            '  • Medium speed with telegraphed movement',
            '  • Instant game over (pushes player off screen)',
            '  • Continuous wind whoosh sound'
        ]
        
        y_pos = 0.28
        for note in behavior_notes:
            if note.startswith('  •'):
                ax.text(0.53, y_pos, note, fontsize=10, transform=ax.transAxes)
            elif note.endswith(':'):
                ax.text(0.5, y_pos, note, fontsize=11, weight='bold', transform=ax.transAxes)
            else:
                ax.text(0.5, y_pos, note, fontsize=10, transform=ax.transAxes)
            y_pos -= 0.02
        
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.axis('off')
        pdf.savefig(fig, bbox_inches='tight', dpi=300)
        plt.close()
        
        # Page 6: UI Elements and Particle Effects
        fig, ax = plt.subplots(figsize=(8.5, 11))
        fig.suptitle('UI SPRITES & PARTICLE EFFECTS', fontsize=20, weight='bold', y=0.95)
        
        # UI Elements section
        ax.text(0.05, 0.88, 'USER INTERFACE ELEMENTS', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        # Life Hearts (24x24)
        ax.text(0.05, 0.82, 'Life Hearts (24×24 pixels):', fontsize=12, weight='bold', 
                transform=ax.transAxes)
        
        heart_states = [('Full Health', '#FF4500', 0.25), ('Half Health', '#FFA500', 0.35), 
                       ('Empty', '#696969', 0.45)]
        for state, color, x in heart_states:
            # Draw heart shape
            heart_size = 0.03
            # Heart is made of two circles and a triangle
            circle1 = patches.Circle((x-heart_size/3, 0.78), heart_size/2, facecolor=color, 
                                   edgecolor='black', transform=ax.transAxes)
            circle2 = patches.Circle((x+heart_size/3, 0.78), heart_size/2, facecolor=color, 
                                   edgecolor='black', transform=ax.transAxes)
            triangle_points = [(x-heart_size, 0.76), (x+heart_size, 0.76), (x, 0.74)]
            triangle = patches.Polygon(triangle_points, facecolor=color, edgecolor='black', 
                                     transform=ax.transAxes)
            ax.add_patch(circle1)
            ax.add_patch(circle2)
            ax.add_patch(triangle)
            
            ax.text(x, 0.72, state, fontsize=10, ha='center', weight='bold', transform=ax.transAxes)
            ax.text(x, 0.69, '24×24px', fontsize=8, ha='center', transform=ax.transAxes)
        
        # Checkpoint Flag (32x64)
        ax.text(0.05, 0.62, 'Checkpoint Flag (32×64 pixels):', fontsize=12, weight='bold', 
                transform=ax.transAxes)
        
        x, y = 0.25, 0.55
        # Flag pole
        pole = patches.Rectangle((x-0.002, y-0.08), 0.004, 0.16, facecolor='white', 
                               edgecolor='black', transform=ax.transAxes)
        ax.add_patch(pole)
        
        # Flag (4 animation frames shown)
        flag_frames = [(x+0.01, y+0.04, 'Frame 1'), (x+0.015, y+0.04, 'Frame 2'),
                      (x+0.02, y+0.04, 'Frame 3'), (x+0.015, y+0.04, 'Frame 4')]
        
        for i, (fx, fy, frame_name) in enumerate(flag_frames):
            flag_x = x + 0.05 + (i * 0.1)
            flag = patches.Polygon([(flag_x, fy+0.02), (flag_x+0.04, fy+0.015), 
                                  (flag_x+0.04, fy-0.015), (flag_x, fy-0.02)], 
                                 facecolor='#FF4500', edgecolor='black', transform=ax.transAxes)
            ax.add_patch(flag)
            ax.text(flag_x+0.02, fy-0.04, frame_name, fontsize=8, ha='center', transform=ax.transAxes)
        
        ax.text(0.45, 0.48, '4-frame waving animation', fontsize=10, weight='bold', transform=ax.transAxes)
        ax.text(0.45, 0.45, '1.5 second cycle', fontsize=9, style='italic', transform=ax.transAxes)
        
        # Particle Effects section
        ax.text(0.05, 0.35, 'PARTICLE EFFECTS', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        # Collection Sparkles (8x8)
        ax.text(0.05, 0.29, 'Collection Sparkles (8×8 pixels):', fontsize=12, weight='bold', 
                transform=ax.transAxes)
        
        sparkle_center = (0.25, 0.25)
        sparkle_positions = [(0.23, 0.27), (0.27, 0.23), (0.22, 0.24), (0.28, 0.26), 
                           (0.24, 0.22), (0.26, 0.28)]
        
        for i, (sx, sy) in enumerate(sparkle_positions):
            alpha = 1.0 - (i * 0.15)  # Fade effect
            sparkle = patches.RegularPolygon((sx, sy), 4, 0.008, orientation=np.pi/4,
                                           facecolor='#FFD700', alpha=alpha, 
                                           edgecolor='white', transform=ax.transAxes)
            ax.add_patch(sparkle)
        
        ax.text(0.35, 0.25, '6-frame burst effect', fontsize=10, weight='bold', transform=ax.transAxes)
        ax.text(0.35, 0.22, '0.5 second duration', fontsize=9, style='italic', transform=ax.transAxes)
        
        # Dust Particles (4x4)
        ax.text(0.05, 0.15, 'Dust Particles (4×4 pixels):', fontsize=12, weight='bold', 
                transform=ax.transAxes)
        
        dust_positions = [(0.22, 0.11), (0.24, 0.09), (0.26, 0.10), (0.28, 0.08)]
        for i, (dx, dy) in enumerate(dust_positions):
            alpha = 0.8 - (i * 0.2)  # Fade out effect
            dust = patches.Circle((dx, dy), 0.004, facecolor='#8B4513', alpha=alpha, 
                                transform=ax.transAxes)
            ax.add_patch(dust)
        
        ax.text(0.35, 0.1, 'Fade out over 1 second', fontsize=10, weight='bold', transform=ax.transAxes)
        ax.text(0.35, 0.07, 'Triggered by landing/direction change', fontsize=9, style='italic', transform=ax.transAxes)
        
        # Water Splash (16x16)
        ax.text(0.55, 0.29, 'Water Splash (16×16 pixels):', fontsize=12, weight='bold', 
                transform=ax.transAxes)
        
        splash_x, splash_y = 0.7, 0.25
        # 4-frame splash animation
        for i in range(4):
            frame_x = splash_x + (i * 0.03) - 0.045
            frame_height = 0.02 + (i * 0.01) if i < 2 else 0.04 - ((i-2) * 0.01)
            
            splash_drops = []
            for j in range(3):
                drop_x = frame_x + (j * 0.01) - 0.01
                drop_y = splash_y + (frame_height * (0.5 + j * 0.2))
                drop = patches.Circle((drop_x, drop_y), 0.002, facecolor='#87CEEB', 
                                    alpha=0.8, transform=ax.transAxes)
                ax.add_patch(drop)
        
        ax.text(0.7, 0.21, '4-frame splash sequence', fontsize=10, weight='bold', transform=ax.transAxes)
        ax.text(0.7, 0.18, '0.3 second duration', fontsize=9, style='italic', transform=ax.transAxes)
        
        # Implementation notes
        ax.text(0.55, 0.15, 'IMPLEMENTATION NOTES:', fontsize=12, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        impl_notes = [
            '• All UI elements positioned consistently',
            '• Hearts pulse when health is low',
            '• Particle effects use object pooling',
            '• Effects scale with screen resolution',
            '• Transparent PNG format for all sprites'
        ]
        
        y_pos = 0.11
        for note in impl_notes:
            ax.text(0.55, y_pos, note, fontsize=10, transform=ax.transAxes)
            y_pos -= 0.02
        
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.axis('off')
        pdf.savefig(fig, bbox_inches='tight', dpi=300)
        plt.close()
        
        # Page 7: Technical Specifications
        fig, ax = plt.subplots(figsize=(8.5, 11))
        fig.suptitle('TECHNICAL SPECIFICATIONS & IMPLEMENTATION', fontsize=20, weight='bold', y=0.95)
        
        # File structure
        ax.text(0.05, 0.88, 'RECOMMENDED FILE STRUCTURE', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        file_structure = [
            '/assets/sprites/',
            '├── player/',
            '│   ├── duck_idle_32x32.png',
            '│   ├── duck_walk_32x32.png',
            '│   └── duck_jump_32x32.png',
            '├── enemies/',
            '│   ├── bear_idle_48x48.png',
            '│   ├── bear_walk_48x48.png',
            '│   ├── bee_fly_24x24.png',
            '│   └── tornado_spin_64x96.png',
            '├── collectibles/',
            '│   ├── seed_float_16x16.png',
            '│   ├── feather_rotate_24x24.png',
            '│   └── potion_bubble_20x32.png',
            '├── environment/',
            '│   ├── grass_variants_32x32.png',
            '│   ├── stone_blocks_32x32.png',
            '│   ├── clouds_drift_64x32.png',
            '│   └── trees_sway_48x64.png',
            '├── ui/',
            '│   ├── hearts_24x24.png',
            '│   ├── flag_wave_32x64.png',
            '│   └── score_font_16px.png',
            '└── effects/',
            '    ├── sparkles_8x8.png',
            '    ├── dust_4x4.png',
            '    └── splash_16x16.png'
        ]
        
        y_pos = 0.84
        for line in file_structure:
            if line.startswith('/assets'):
                ax.text(0.05, y_pos, line, fontsize=11, weight='bold', transform=ax.transAxes)
            elif line.startswith('├──') or line.startswith('└──'):
                ax.text(0.05, y_pos, line, fontsize=10, weight='bold', color='#2E4057', transform=ax.transAxes)
            else:
                ax.text(0.05, y_pos, line, fontsize=9, family='monospace', transform=ax.transAxes)
            y_pos -= 0.02
        
        # Sprite sheet format
        ax.text(0.5, 0.88, 'SPRITE SHEET FORMAT', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        # Example sprite sheet visualization
        sheet_x, sheet_y = 0.7, 0.8
        sheet_width, sheet_height = 0.25, 0.08
        
        # Background
        sheet_bg = patches.Rectangle((sheet_x-sheet_width/2, sheet_y-sheet_height/2), 
                                   sheet_width, sheet_height, facecolor='white', 
                                   edgecolor='black', linewidth=2, transform=ax.transAxes)
        ax.add_patch(sheet_bg)
        
        # Individual frames
        frame_width = sheet_width / 4
        for i in range(4):
            frame_x = sheet_x - sheet_width/2 + (i * frame_width) + frame_width/2
            frame = patches.Rectangle((frame_x-frame_width/2+0.005, sheet_y-sheet_height/2+0.005), 
                                    frame_width-0.01, sheet_height-0.01, facecolor='#FFD700', 
                                    edgecolor='black', linewidth=1, transform=ax.transAxes)
            ax.add_patch(frame)
            ax.text(frame_x, sheet_y, str(i+1), fontsize=8, ha='center', va='center', 
                   weight='bold', transform=ax.transAxes)
        
        ax.text(sheet_x, sheet_y-0.06, 'Horizontal sprite sheet layout', fontsize=10, 
               ha='center', weight='bold', transform=ax.transAxes)
        ax.text(sheet_x, sheet_y-0.09, 'Frame 1 | Frame 2 | Frame 3 | Frame 4', fontsize=9, 
               ha='center', style='italic', transform=ax.transAxes)
        
        # Performance optimization
        ax.text(0.05, 0.45, 'PERFORMANCE OPTIMIZATION', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        perf_tips = [
            'SPRITE OPTIMIZATION:',
            '  • Use PNG format with alpha transparency',
            '  • Optimize file sizes with tools like TinyPNG',
            '  • Power-of-2 dimensions when possible (16, 32, 64, etc.)',
            '  • Use sprite atlases to reduce draw calls',
            '',
            'ANIMATION EFFICIENCY:',
            '  • Limit concurrent particle effects (max 50)',
            '  • Use object pooling for frequently created/destroyed objects',
            '  • Cache sprite textures in memory',
            '  • Implement sprite culling for off-screen objects',
            '',
            'MEMORY MANAGEMENT:',
            '  • Preload all sprites at game start',
            '  • Use texture compression where supported',
            '  • Implement mipmap generation for scaling',
            '  • Unload unused sprites during level transitions',
            '',
            'RENDERING OPTIMIZATION:',
            '  • Batch similar sprites in single draw calls',
            '  • Use vertex buffer objects (VBOs) for static geometry',
            '  • Implement frustum culling for large levels',
            '  • Consider using sprite instancing for repeated elements'
        ]
        
        y_pos = 0.41
        for tip in perf_tips:
            if tip.startswith('  •'):
                ax.text(0.08, y_pos, tip, fontsize=10, transform=ax.transAxes)
            elif tip.endswith(':'):
                ax.text(0.05, y_pos, tip, fontsize=11, weight='bold', transform=ax.transAxes)
            else:
                ax.text(0.05, y_pos, tip, fontsize=10, transform=ax.transAxes)
            y_pos -= 0.02
        
        # Quality assurance
        ax.text(0.5, 0.45, 'QUALITY ASSURANCE CHECKLIST', fontsize=16, weight='bold', 
                transform=ax.transAxes, color='#2E4057')
        
        qa_checklist = [
            '☑ All sprites align to 16×16 pixel grid',
            '☑ Consistent lighting direction (top-left)',
            '☑ Proper alpha channel transparency',
            '☑ No color bleeding on sprite edges',
            '☑ Animations loop smoothly',
            '☑ Readable at different zoom levels',
            '☑ Consistent art style throughout',
            '☑ Proper file naming convention',
            '☑ Optimized file sizes',
            '☑ Cross-platform compatibility tested',
            '',
            'FINAL VALIDATION:',
            '☑ All sprites load correctly in game engine',
            '☑ Animation timing matches specifications',
            '☑ Color palette consistency maintained',
            '☑ Performance benchmarks met',
            '☑ Accessibility guidelines followed'
        ]
        
        y_pos = 0.41
        for item in qa_checklist:
            if item.startswith('☑'):
                ax.text(0.5, y_pos, item, fontsize=10, transform=ax.transAxes, color='#228B22')
            elif item.endswith(':'):
                ax.text(0.5, y_pos, item, fontsize=11, weight='bold', transform=ax.transAxes)
            else:
                ax.text(0.5, y_pos, item, fontsize=10, transform=ax.transAxes)
            y_pos -= 0.02
        
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.axis('off')
        pdf.savefig(fig, bbox_inches='tight', dpi=300)
        plt.close()
    
    print("✅ PDF created successfully: Duck_Dash_Sprite_Reference.pdf")
    print("📄 7 pages with comprehensive sprite specifications")
    print("🎨 Includes visual representations, sizing, and technical details")

if __name__ == "__main__":
    create_sprite_pdf()